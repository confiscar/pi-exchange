#!/bin/bash

echo '                                                                                         
                                                                                                    
                                      /ydmmmmmmmmmmmmdy-                                            
                                     /MMMMMMMMMMMMMMMMMN.                                           
                                     +MMMMMMMMMMMMMMMMMM-                                           
                      `/++-          +MMMMMd/////+NMMMMM-         `:++:`                            
                    `+mMMMNh:    `-/smMMMMMh     `mMMMMMho/-`   `/dNMMNd/                           
                  `+mMMMMMMMNh/ohmNMMMMMMMMs     `dMMMMMMMMNmh+/dMMMMMMMMd/`                        
                `+dMMMMMMMMMMMMMMMMMMMMNmho`      -sdmNMMMMMMMMMMMMMMMMMMMNh:                       
              `/dMMMMMMNshNMMMMMMMNhs/-.``          ``.-+ydNMMMMMMMNsyNMMMMMNh:                     
             /dMMMMMMNs. `:hNMNms/.`                      `./ymMMms-  -yNMMMMMNh-                   
            .NMMMMMMd-      .--`                              .--.      /NMMMMMMd                   
             sNMMMMMNh:                                               `/dMMMMMMm/                   
              -yNMMMMMNs                                             `hMMMMMMmo.                    
                :NMMMMMd                   ``....``                  .mMMMMMm.                      
               `yMMMMMh.              `./shdmmNNmmdho:.               -mMMMMMo                      
               sMMMMMh`             .+hNMMMMMMMMMMMMMMmh/`             .mMMMMN/                     
        ``````/MMMMMd`            `oNMMMMMMMMNNNNMMMMMMMMm/`            -NMMMMm.`````               
      `ohdddddNMMMMM-            :dMMMMMMmy+:-.--/ohNMMMMMMh`            +MMMMMmdddddh+             
      yMMMMMMMMMMMMs            :NMMMMMm/`          .oNMMMMMd.           `dMMMMMMMMMMMM/            
      dMMMMMMMMMMNd.           `NMMMMMy`              -mMMMMMy            :mMMMMMMMMMMMo            
      dMMMMMy::::-             oMMMMMm`                -MMMMMM-            `:::::dMMMMMo            
      dMMMMM+                  yMMMMMo                  dMMMMM/                  hMMMMMo            
      dMMMMM+                  yMMMMMs                  dMMMMM/                  hMMMMMo            
      dMMMMMhooo+/`            +MMMMMm.                :MMMMMN-            .+oooomMMMMMo            
      dMMMMMMMMMMMm.            dMMMMMd.              :NMMMMMs            /NMMMMMMMMMMMo            
      sMMMMMMMMMMMMy            .mMMMMMNs-          :yMMMMMMh`           `mMMMMMMMMMMMM:            
       /syyyyymMMMMM-            .hMMMMMMMmy+/::/oymMMMMMMMs             oMMMMMhyyyyys-             
              :NMMMMm.             /dMMMMMMMMMMMMMMMMMMMMh-             /MMMMMd`                    
               +MMMMMd.             `:smMMMMMMMMMMMMMNdo.              :NMMMMN-                     
                sMMMMMm-               `-/oyhddddhyo:.`               +NMMMMN:                      
               `+NMMMMMm                     ````                    .NMMMMMm:                      
             `/dMMMMMMN+                                             `sNMMMMMNh:                    
            `hMMMMMMNs.                                                -yNMMMMMNs                   
            `NMMMMMMm:     `:+/-`                            `-/+:`    `+NMMMMMMh                   
             -yNMMMMMNh: `+mMMMNdo:.                     `.:sdNMMNh/``/dMMMMMMNs`                   
               -yNMMMMMNhdMMMMMMMMMmds+:-.         `.-:+ydNMMMMMMMMMhdMMMMMMNs.                     
                 :hNMMMMMMMMMMNMMMMMMMMMNmh-      :dmNMMMMMMMMMNMMMMMMMMMMNs.                       
                   :hNMMMMMMmo-:shmNMMMMMMMy     `mMMMMMMMNmho:-yNMMMMMMNs-                         
                     :hNMMms.     .-/hMMMMMh     `mMMMMMs/-`     -yNMMNy-                           
                       -::.          +MMMMMmssssssNMMMMM-          .::.                             
                                     +MMMMMMMMMMMMMMMMMM-                                           
                                     :NMMMMMMMMMMMMMMMMm`                                           
                                      -osyyyyyyyyyyyys+.        '

sleep 1

echo 'Getting dependences for PI-EXCHANGE'
sleep 1
echo '.'
sleep 1
echo '..'
sleep 1
echo '...'
sudo apt-get update -y
echo -e $TEXT_YELLOW
echo 'APT update finished...'
echo -e $TEXT_RESET

sudo apt-get dist-upgrade -y
echo -e $TEXT_YELLOW
echo 'APT distributive upgrade finished...'
echo -e $TEXT_RESET

sudo apt-get upgrade -y
echo -e $TEXT_YELLOW
echo 'APT upgrade finished...'
echo -e $TEXT_RESET
 
sudo add-apt-repository ppa:linuxuprising/java
echo -e $TEXT_YELLOW
echo 'Added Repository...'
echo -e $TEXT_RESET
sudo apt-get update -y
echo -e $TEXT_YELLOW
echo 'APT update finished...'
echo -e $TEXT_RESET
sudo apt-get install oracle-java10-installer
echo -e $TEXT_YELLOW
echo 'finished installing Java 10'
echo -e $TEXT_RESET

sudo apt install python3-pip
echo -e $TEXT_YELLOW
echo 'finished installing Python3'
echo -e $TEXT_RESET


sudo pip install psutil
echo -e $TEXT_YELLOW
echo 'finished installing psutil'
echo -e $TEXT_RESET


sudo pip install feedparser
echo -e $TEXT_YELLOW
echo 'finished installing Feedparser'
echo -e $TEXT_RESET

sudo apt-get autoremove
echo -e $TEXT_YELLOW
echo 'APT auto remove finished...'
echo -e $TEXT_RESET
echo -e $TEXT_BLUE
echo 'Your device is ready for Battle'
echo -e $TEXT_RESET

if [ -f /var/run/reboot-required ]; then
    echo -e $TEXT_RED_B
    echo 'Reboot required!'
    echo -e $TEXT_RESET
fi
