To print compression ratio use (-ratio)
---------------------------------------------------------------------------------------------------------
To print compression ratio with encode use (-ratioWencode)
---------------------------------------------------------------------------------------------------------
To encode then decode an image:
./hw1_p3 -encode 1024 256 256 < ./data/(file name).pgm | ./hw1_p3 -decode 256 256 255 (file name)

_ last file name is optional if you didn't enter file name at the end of the command the image output under name output as ./output/output.pgm _

e.g: ./hw1_p3 -encode 1024 256 256 < ./data/sena.pgm | ./hw1_p3 -decode 256 256 255 sena
---------------------------------------------------------------------------------------------------------
./hw1_p3 -encode S T A -file (fileName) < ./data/(fileName).pgm
=> senaEncode file is created has encode of sena.pgm
=> if you don't use -file encoded message will print on console
---------------------------------------------------------------------------------------------------------
./hw1_p3 -encode 1024 256 256 -file sena < ./data/sena.pgm
=> senaEncode file is created has encode of sena.pgm
=> if you don't use -file encoded message will print on console
---------------------------------------------------------------------------------------------------------
To encode all images without diff:
./hw1_p3 -encode 1024 256 256 -file earth < ./data/earth.pgm && ./hw1_p3 -encode 1024 256 256 -file sensin < ./data/sensin.pgm && ./hw1_p3 -encode 1024 256 256 -file omaha < ./data/omaha.pgm && ./hw1_p3 -encode 1024 256 256 -file sena < ./data/sena.pgm
---------------------------------------------------------------------------------------------------------
To encode all images with diff:
./hw1_p3 -encode -diff 1024 256 256 -file earth_Diff < ./data/earth.pgm && ./hw1_p3 -encode -diff 1024 256 256 -file sensin_Diff < ./data/sensin.pgm && ./hw1_p3 -encode -diff 1024 256 256 -file omaha_Diff < ./data/omaha.pgm && ./hw1_p3 -encode -diff 1024 256 256 -file sena_Diff < ./data/sena.pgm
---------------------------------------------------------------------------------------------------------
