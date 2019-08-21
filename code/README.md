## Run

`$ make`

`$ ./<program-name> <array_size> <threshold> <num_threads>`

Except for serial versions which do not have `<num_threads>`.


## Scripts

There are 3 included scripts:

- `run-all-tests.sh`: will run all programs and store their results in their respective folders. Parameters such as threshold and array size can be tweaked here manually.

- `run-single-pgm-tests.sh`: runs tests for a single program only, specify which program manually in the script.

- `clear-results.sh`: removes all test output files from results directories.


## Clean

`$ make clean`


### Other Codes

The directory `other_codes` contains codes developed but not discussed in paper.
