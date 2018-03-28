const fs = require('fs');
const path = require('path');
const async = require('async');
const https = require('https');

const requestRoutes = (api, routes, next) => {
    const directions = [];
    const q = async.queue((route, cb) => {
        let coords = route.features.features.map(f => f.geometry.coordinates.join(',')).join(';');
        const requestOptions = `${coords}?access_token=${token}&overview=full&annotations=nodes,maxspeed`;
        const options = {
            hostname: api,
            method: 'GET',
            path: `/directions/v5/mapbox/driving/${requestOptions}`
        };
        console.log(`Requesting ${route.name}`);
        const req = https.request(options, (res) => {
            let response = {name: route.name, body: ''};
            res.setEncoding('utf8');
            res.on('data', (c) => {
                response.body += c;
            });
            res.on('end', () => {
                response.body = JSON.parse(response.body);
                return cb(response);
            });
        });
        req.on('error', (err) => {
            response.body = null;
            return cb(response);
        });
        req.end();
    }, 4);
    // queue up test routes
    for (let i = 0; i < routes.length; i++) {
        q.push(routes[i], (res) => {
            directions.push(res);
        });
    }
    // exit
    q.drain = () => {
        return next(null, directions);
    }
};

const getRoutes = (filePath, next) => {
    fs.readFile(filePath, 'utf8', (err, data) => {
        if (err) return next(err);
        data = JSON.parse(data);
        return next(null, data);
    });
};

const analyze = (response) => {
    const result = {
        name: response.name,
        weirdos: [], // values that don't end in 0 or 5
        num_unknowns: 0,
        unknown_streak: 0,
        total_maxspeeds: 0,
        pct_unknowns: 0,
        num_nones: 0,
        err: ''
    };
    if (!response.body.routes) {
        result.err = 'no routes';
        return result;
    }
    response.body.routes[0].legs.forEach((leg) => {
        let maxspeeds = leg.annotation.maxspeed;
        let nodes = leg.annotation.nodes;

        result.total_maxspeeds += leg.annotation.maxspeed.length;

        let streak = 0;
        let previous_unknown = false;
        for (let i = 0; i < maxspeeds.length; i++) {
            let current_ms = maxspeeds[i];
            let current_node = nodes[i];
            if (maxspeeds[i - 1] && maxspeeds[i - 1].unknown) previous_unknown = true;

            if (current_ms.unknown) {
                result.num_unknowns++;
                streak++;
            } else {
                streak = 0;
            }

            if (current_ms.speed) {
                let endsZeroOrFive = current_ms.speed % 2 === 0 || current_ms.speed % 5 === 0;
                if (!endsZeroOrFive) {
                    result.weirdos.push({maxspeed: current_ms, nodes: [current_node, nodes[i + 1]]});
                }
            }
            if (current_ms.none) {
                result.num_nones++;
            }
            result.unknown_streak = Math.max(result.unknown_streak, streak);
        }
    });
    result.pct_unknowns = Math.ceil((result.num_unknowns / result.total_maxspeeds) * 100);
    console.log(result);
    return result;
};
const run = (config) => {
    getRoutes(config.file, (err, data) => {
        if (err) throw err;
        requestRoutes(config.endpoint, data.routes, (err, results) => {
            if (err) throw err;
            // analyze results
            const analysis = results.map(analyze);
            fs.writeFile('./results', JSON.stringify(analysis, null, 2), (err) => {
                if (err) {
                    console.error('error writing to results file');
                    console.log(JSON.stringify(analysis, null, 2));
                }
                fs.writeFile('./roh', JSON.stringify(results, null, 2), (err) => {
                    if (err) {
                        console.error('error writing to raw file');
                        console.log(JSON.stringify(results, null, 2));
                    }
                });
            });
        });
    });
}

if (require.main === module) {
    var token = process.env.MAPBOX_API_TOKEN;
    if (!token) throw new Error('Please set $MAPBOX_API_TOKEN and rerun');

    let config = {
        endpoint: process.argv[2] || 'api.mapbox.com',
        file: process.argv[3] || 'routes.json'
    };
    run(config);
}

module.exports.run = run;
module.exports.getRoutes = getRoutes;
module.exports.requestRoutes = requestRoutes;
