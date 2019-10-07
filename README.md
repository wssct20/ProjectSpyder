# ProjectSpyder
SmartHome by WSSCT20

## How to install
The Software runs on Apache2 in the root web folder using a symlink to the Projects current Git Clone.
The following shell commands will create a file named "updatefromgit.sh" which should be run every once in a while to update to the current version. You need to run the script at least once to get the latest files.
```
cd /var/www
ln -s -T /var/www/ProjectSpyder html
echo '#!/bin/sh' > updatefromgit.sh
echo "cd /var/www" >> updatefromgit.sh
echo "git clone https://github.com/wssct20/ProjectSpyder.git tmp" >> updatefromgit.sh
echo "cp -rv tmp/. ProjectSpyder/" >> updatefromgit.sh
echo "rm -rfv tmp" >> updatefromgit.sh
chmod +x updatefromgit.sh
./updatefromgit.sh
```

crontab makes it easy to keep up to date:
```
@reboot sleep 15 && sh /var/www/updatefromgit.sh
# sleeping 15s to ensure network is up
```
