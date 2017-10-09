const fs = require('fs');
const request = require('request');
const turf = require('@turf/helpers');

const uri = process.argv[2] || '';
const profile = process.argv[3] || '';
const token = process.env.MBXACCESSTOKEN;
const debug = process.env.DEBUG || false;
const geometries = __dirname + '/geometries';

if (!token) throw new Error('Set $MBXACCESSTOKEN')
if (!uri) throw new Error('Missing uri argument');
if (!profile) throw new Error('Missing profile argument');

var paths = {
    v5: {
        directions: `directions/v5/mapbox/${profile}`,
        matching: `matching/v5/mapbox/${profile}`,
    },
    v1: {
        matrix: `directions-matrix/v1/mapbox/${profile}`,
        distances: `distances/v1/mapbox/${profile}`,
        optimize: `optimized-trips/v1/mapbox/${profile}`
    },
    v4: {
        directions: `v4/directions/mapbox.${profile}`,
        matching: `matching/v4/mapbox.${profile}`,
    }
};

function makeOptions(method, version, service) {
    let options = {
        rejectUnauthorized: false
    };
    if (method === 'POST') {
        options.method = 'POST';
        options.json = true;
        options.url = 'https://' + uri + '/' + paths[version][service] + '?access_token=' + token;
    } else {
        options.method = 'GET';
        options.base = 'https://' + uri + '/' + paths[version][service];
        options.token = `.json?access_token=${token}`;
    }
    return options;
}

function getFiles(service, cb) {
    fs.readdir(`${geometries}/${service}`, (err, files) => {
        if (err) throw err;
        cb(files);
    });
}

function getCoords(service, file, cb) {
    var service_map = {
        'distances': 'matrix',
        'directions': 'routing',
        'driving-traffic': 'routing',
        'optimize': 'routing'
    };
    let s = service_map[service] || service;
    fs.readFile(`${geometries}/${s}/${file}`, (err, data) => {
        if (err) throw err;
        data = JSON.parse(data);
        cb(data);
    });
}

function handleResponse(err, res, options, service, file) {
    if (err) throw err;
    if (res.statusCode != 200) {
        console.log(`FAIL - ${res.statusCode}, ${service} : ${file}`);
        console.log(`------ ${options.method} to ${options.url}`);
    } else {
        if (debug) console.log(options.url);
        console.log(`OK --- ${res.statusCode}, ${service}`);
    }
}

function makev1Request(service, file) {
    let options;
    getCoords(service, file, (data) => {
        if (service === 'distances') {
            options = makeOptions('POST', 'v1', service);
            options.body = { coordinates: data.features.map(f => f.geometry.coordinates) };
        } else {
            options = makeOptions('GET', 'v1', service);
            let coords = data.features.map(f => f.geometry.coordinates).join(';');
            options.url = `${options.base}/${coords}${options.token}`;
        }
        request(options, (err, res) => {
            handleResponse(err, res, options, `v1 ${service}`, file);
        });
    });
}

function makev4Request(service, file) {
    getCoords(service, file, (data) => {
        if (service === 'matching') {
            options = makeOptions('POST', 'v4', service);
            options.url = options.url.split('?').join('.json?');
            options.body = turf.lineString(data.features.map(f => f.geometry.coordinates));
        } else {
            options = makeOptions('GET', 'v4', service);
            // if profile is 'driving-traffic' cut down coords to 3 because of hardcoded limit
            if (profile === 'driving-traffic') data.features = data.features.slice(0, 3);
            let coords = data.features.map(f => f.geometry.coordinates).join(';');
            options.url = `${options.base}/${coords}${options.token}`;
        }
        request(options, (err, res) => {
            handleResponse(err, res, options, `v4 ${service}`, file);
        });
    });
}

function makev5Request(service, file) {
    getCoords(service, file, (data) => {
        options = makeOptions('GET', 'v5', service);
        let coords = data.features.map(f => f.geometry.coordinates).join(';');
        options.url = `${options.base}/${coords}${options.token}`;
        request(options, (err, res) => {
            handleResponse(err, res, options, `v5 ${service}`, file);
        });
    });
}

getFiles('matching', (files) => {
    for (let i = 0; i < files.length; i++) {
        makev5Request('matching', files[i]);
        makev4Request('matching', files[i]);
    }
});
getFiles('matrix', (files) => {
    for (let i = 0; i < files.length; i++) {
        makev1Request('matrix', files[i]);
        makev1Request('distances', files[i]);
    }
});

getFiles('routing', (files) => {
    for (let i = 0; i < files.length; i++) {
        makev5Request('directions', files[i]);
        makev4Request('directions', files[i]);
        if (profile != 'driving-traffic') makev1Request('optimize', files[i]);
    }
});
