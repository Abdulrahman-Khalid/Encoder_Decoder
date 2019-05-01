To print compression ratio use (-ratio) after encode command
----------------------------------------------------------------------------------------------------------
To print compression ratio with encode use (-ratioWencode) after encode command
----------------------------------------------------------------------------------------------------------
To encode then decode all images in /output/ directory:

./hw1_p2 -encode 3 < ./data/sena.pgm | ./hw1_p2 -decode 3 256 256 255 sena && ./hw1_p2 -encode 3 < ./data/sensin.pgm | ./hw1_p2 -decode 3 256 256 255 sensin && ./hw1_p2 -encode 3 < ./data/omaha.pgm | ./hw1_p2 -decode 3 256 256 255 omaha && ./hw1_p2 -encode 3 < ./data/earth.pgm | ./hw1_p2 -decode 3 256 256 255 earth && ./hw1_p2 -encode 3 < ./data/msg2.pgm | ./hw1_p2 -decode 3 3 3 255 msg2 && ./hw1_p2 -encode 3 < ./data/msg3.pgm | ./hw1_p2 -decode 3 24 7 255 msg3 && ./hw1_p2 -encode 3 < ./data/msg1.pgm | ./hw1_p2 -decode 3 5 2 255 msg1
----------------------------------------------------------------------------------------------------------
To encode all images in files in /output/Encode/ directory:

./hw1_p2 -encode 3 -file sena < ./data/sena.pgm && ./hw1_p2 -encode 3 -file sensin < ./data/sensin.pgm && ./hw1_p2 -encode 3 -file omaha < ./data/omaha.pgm && ./hw1_p2 -encode 3 -file omaha < ./data/earth.pgm -file earth && ./hw1_p2 -encode 3 -file msg2 < ./data/msg2.pgm && ./hw1_p2 -encode 3 -file msg3 < ./data/msg3.pgm && ./hw1_p2 -encode 3 -file msg1 < ./data/msg1.pgm
----------------------------------------------------------------------------------------------------------
