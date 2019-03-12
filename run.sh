#!/bin/bash

echo -e $TEXT_RED
echo ' ``::+o+ss///--`           `--///ss+o+::``                              
                         :/sdddNmmmhmddNdNmmo+.     .+ommNmNmdmddmmNmdds/:                          
                        -MNhhyssooooooosossymmmo` `oNmdhssosooooooossshhNM-                         
                        /MNyoooooooooooooooooohMy`yMhoooooooooooooooooosNM/                         
                        .MNhoooooosyyysoooooooohMdMdoooooooossyysooooooyNM.                         
                         sMmsoooooooosyhhyooooooMMMsoooooshhysoooooooosdMs                          
                         `hMdsooooooooooshddyosdMMMmsoshdhsoooooooooosdMh`                          
                          `hNmsooooooooooooyNNNMMMMMNmNhsooooooooooosdNh`                           
                           `:mMdyoooooooooosNMMMMMMMMMNyooooooooooshNm:`                            
                             .:hNmhhysssshmMMMMMMMMMMMMMmhysssshhmNh:.  `````````                   
                               .sNMMNmmNNMMMNmddhhhhdmNMMMNNNNNMMNs.    -///////:                   
                             .sNNmdhhyyhmMNdhyyyyys+yyhdNNhhhhhdmNMNs.   `/+++++/                   
                            /NMdhyyyyhdNMMdyyyyyys+++yyydMNdhyyyyhdNMN/ ./+++/++/                   
                           .NMhyyyyhmNMMMMMmdhhys++++shdNMMMNmhyyyyhMMd/++++/.-//                   
                           oMNyyhdmMMMMNNmNNMMNy++++++mmmdmmNMMmdhyydy++++/-   `.                   
                          -+dNdmNMMMmhhyyyyyhdh+++++++oyyyyyyhdNMNms+++++:`                         
                        ./+++NMMMMmhyyyyyyyyys+++++++++syyyyyyyydms++++oh/                          
                       :+++++oNMMmyyyyyyyyyys++++oN+++++yyyyyyyyo+++++sdMMd.                        
                     ./+++++++yMMhyyyyyyyyys++++oNMy++++oyyyyys+++++oyyyhNMN.                       
                   `:+++++s++++dNyyyyyyyyys++++oNMMNo++++yyyy+++++omhyyyyhMMh                       
                  -/++++syyo++++Ndyyyyyyys++++oNMMMMm++++oyo+++++yMMdyyyyhMMN                       
                `/++++oNmyyy++++oNdhyyyys++++oNMNNNMMh+++++++++smMMMNyyyyhMMd                       
               -/+++/.-NMdyyy++++yMMNmdy+++++hhhhhhhhdo++++++omMMMMMMdyyhNMN-                       
             ./+++/-   -mMmmNd++++dMMMm+++++yyyyyyyyyyy+++++hMMMNmdhdNmmMMm-                        
           `:/+++:`     `NMMNho++++mMm+++++yyyyyyyyyyyyo++yNMMmhhyyyyhMMMN`                         
            `````        +MMmyy++++oy+++++yyyyyyyyyyyyyyohMMmhyyyyyyyymMM+                          
                          hMmyyy++++++++omhyyyyyyyyyyyyyyNMmhyyyyyyyyyNMh                           
                          -MMdyys+++++++mMNhyyyyyyyyyyyhmMNyyyyyyyyyydMM-                           
                           +NMdhyo+++++yNMMMNdhhhhhhhdmNMMdyyyyyyyyhdMN+                            
                            -hMNdh++++yhNMMMMMMNNNNNMMMMMMdyyyyyyhdNMh-                             
                             `:smNd++dmNMMMNNmdddddddmmNMMMmmdmmNNms:`                              
                                `-++dMMMMNhhyyyyyyyyyyyhhMMMMMNd+-`                                 
                                    -+ymNMmhyyyyyyyyyyhhmMNmy+-                                     
                                       `-omNNmdhhhhhdmNNdo-`                                        
                                          `:ohmmmmmdyo/.                                            
                                              ``..`                             
'
echo -e $TEXT_RESET





echo -e $TEXT_RED
echo 'System is getting fired up'
echo -e $TEXT_RESET


echo -e $TEXT_RED
echo 'Waiting for 2 seconds.....'
echo -e $TEXT_RESET
 
sleep 2

echo -e $TEXT_RED
echo 'Runnig Server'
echo -e $TEXT_RESET

cd "src/server/"

wait 1

./runserver.sh &
echo -e $TEXT_RED
echo 'Waiting for 2 seconds.....'
echo -e $TEXT_RESET

sleep 2

echo -e $TEXT_RED
echo 'Runnig GUI'
echo -e $TEXT_RESET

python3 '/home/blackfalcon/pi-exchange/src/gui/gui-v0.2.py'&

echo -e $TEXT_RED
echo 'Waiting for 2 seconds.....'
echo -e $TEXT_RESET


sleep 2
cd "../"

java -jar bot.jar&
echo -e $TEXT_RED
echo 'Runnig 1 instance for Bot'
echo -e $TEXT_RESET

sleep 1
echo -e $TEXT_RED
echo 'Happy trading'
echo -e $TEXT_RESET

