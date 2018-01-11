#!/usr/bin/env node
'use strict';

const fs = require('fs');

const infile = process.argv[2];
if (!infile) throw Error('pls infile');

fs.readFile(infile, 'utf8', (err, data) => {
    if (err) throw err;
    data = JSON.parse(data);
    const trace_coords = data.geometry.coordinates;
    const trace_coordTimes = data.properties.coordTimes;
    const trace_len = trace_coords.length;
    const range = 5;

    function increment(curr, next) {
        console.log(`${curr} - ${next}`);
        makeTrace(curr, next, data);
        if (next === trace_len) return;
        curr += range;
        next = (next + range) < trace_len ? next + range : trace_len;
        increment(curr, next);
    }
    increment(0, range - 1);
    makeTrace(21, 26, data);
});

function makeTrace(l, r, data) {
    let name = `dnv-${l}-${r}`;
    console.log(name);
    let trace = {
        type: 'Feature',
        properties: {
            coordTimes: []
        },
        geometry: {
            type: 'LineString',
            coordinates: []
        }
    };
    // slice is end-exclusive
    trace.geometry.coordinates = data.geometry.coordinates.slice(l, r + 1);
    trace.properties.coordTimes = data.properties.coordTimes.slice(l, r + 1);
    fs.writeFile(name, JSON.stringify(trace), (err) => {
        if (err) throw err;
    });
};
