#!/bin/bash

for i in {1..80}
do
    url1="http://localhost/junchao/IoT/project/runThermostat5min.php?entryid="
    url=${url1}${i}
    curl ${url}
done
