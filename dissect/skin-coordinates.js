#!/usr/bin/env node
'use strict';

const fs = require('fs');

const infile = process.argv[2] || './test.json';
var arrayify = false;
if (process.argv[3] && ['-a', '--array'].indexOf(process.argv[3]) >= 0) arrayify = true;

fs.readFile(infile, 'utf8', (err, data) => {
    if (err) throw err;
    var justcoords;
    if (arrayify) {
        justcoords = JSON.parse(data).features.map(f => { return f.geometry.coordinates; });
    } else {
        justcoords = JSON.parse(data).features.reduce((all, f) => {
            if (all.length == 0) return f.geometry.coordinates;
            return all + ";" + f.geometry.coordinates;
        }, "");
    }
    console.log(justcoords);
});
