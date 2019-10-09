# ProjectSpyder
SmartHome by WSSCT20

## How to install
The software uses the Apache2 webserver and a MySQL Server.

It runs on Apache2 in the root web folder using a symlink to the Projects current Git Clone.
You may need to run the following commands as root or change the permissions of affected folders
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

To ensure the Server is reachable, we use NETBIOS and/or DNS of the router.
For this you will need to configure your router and set the machines hostname to the correct one.
```
hostname SpyderHub
```

After that you need to setup basic settings and credentials for the MySQL Server.
To do this you need to place a credentials.php into the webroot. Don't worry, its not accessible from outside.
It needs to contain these lines:
```
<?php
$sqluser = "username";
$sqlpass = "password";
$sqldbname = "ProjectSpyder";
?>
```
You need to replace the username with the username of the MySQL Server. Then do the same for the password.
The dbname parameter defines the name of the Database in the MySQL Server.
If you don't have one already, leave it at its default value.

The following lines shall be executed within the sql shell to setup the SQL Server.
```
create database ProjectSpyder;
use ProjectSpyder;
(unfinished, more lines will be added soon)
```

