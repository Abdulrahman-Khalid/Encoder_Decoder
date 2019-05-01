To encode all 4 images:
./hw1_p1 -encode -file sena < ./data/sena.pgm && ./hw1_p1 -encode -file sensin < ./data/sensin.pgm && ./hw1_p1 -encode -file omaha< ./data/omaha.pgm && ./hw1_p1 -encode -file earth < ./data/earth.pgm
----------------------------------------------------------------------------------------------------------
To encode all 4 images using -diff:
./hw1_p1 -encode -diff -file sena_Diff < ./data/sena.pgm && ./hw1_p1 -encode -diff -file sensin_Diff < ./data/sensin.pgm && ./hw1_p1 -encode -diff -file omaha_Diff < ./data/omaha.pgm && ./hw1_p1 -encode -diff -file earth_Diff < ./data/earth.pgm
----------------------------------------------------------------------------------------------------------
Note that: number of bytes and table are printed on console
