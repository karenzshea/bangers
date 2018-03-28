```
$ npm install
$ export MAPBOX_API_TOKEN="a valid api token"
$ node run.js api.mapbox.com ./my_test_routes.json
```

my_test_routes.json is a file containing:
```
{
    "routes": [
        {
            "name": "name of test route",
            "features:" {
                // a geojson feature collection of Point features
            }
        }
    ]
}
```

It will write results to a `results` file and a raw responses to a `raw` file.
