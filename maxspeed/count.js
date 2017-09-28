const osmium = require('osmium');
const ld = require('@turf/line-distance');

const infile = process.argv[2];
if (!infile) {
    console.error('gibs mir infile');
    process.exit(1);
}

const justTags = process.argv[3] ===  'tags' ? true : false;

var total_km = 0;
var total_km_maxspeed = 0;
var tag_store = new Map();

function addTag(k, v, justTag) {
    let key = justTag ? k : `${k}-${v}`;
    let entry = tag_store.has(key);
    if (!entry) tag_store.set(key, 1);
    let orig = tag_store.get(key);
    tag_store.set(key, orig + 1);
}

var reader = new osmium.Reader(infile);
var handler = new osmium.Handler();
var loc_handler = new osmium.LocationHandler('sparse_mmap_array');

handler.on('init', () => {});
handler.on('way', (way) => {
    let ls;
    try {
        ls = way.geojson();
    } catch (e) {
        if (e.message == 'Way has no geometry') return;
        else throw e;
    }
    let distance = ld(ls);
    total_km += distance;
    let tags = way.tags();
    Object.keys(tags).forEach(t => {
        if (t.match(/maxspeed/)) {
            total_km_maxspeed += distance;
            addTag(t, tags[t], justTags);
        }
    });
});

osmium.apply(reader, loc_handler, handler);

console.log('total km of way: ' + total_km);
console.log('total km of way tagged with maxspeed: ' + total_km_maxspeed);
console.log(tag_store);
