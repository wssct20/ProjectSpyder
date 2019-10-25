# ProjectSpyder
SmartHome by WSSCT20

## How to install server
The software uses the Apache2 webserver with PHP enabled and a MySQL Server.

Debian/Raspbian install commands:
```
sudo apt install apache2 mysql php php-mysql
sudo a2enmod php*
```

It runs on Apache2 in the root web folder using a symlink to a git clone of the project.
You may need to run the following commands as root or change the permissions of affected folders
The following shell script will create a file named `updatefromgit.sh`, 
which should be run every once in a while to update to the current version.
You need to run the script at least once to get the latest files.
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

Apache2 is logging all accesses and errors by default. This will fill up your disk quickly.
Please consider [disabling apache2 logging](https://www.mydigitallife.net/how-to-disable-and-turn-off-apache-httpd-access-and-error-log/).

To ensure the Server is reachable, we use NETBIOS and/or DNS of the router.
For this you will need to configure your router and set the machines hostname to the correct one.
If you are using Raspbian, you might need to run raspi-config and change the hostname in there.
```
sudo hostname SpyderHub
```

After that you need to setup basic settings and credentials for the MySQL Server.
To do this you need to place a `credentials.php` into the webroot. Don't worry, its not accessible from outside.
It needs to contain these lines:
```
<?php
$sqluser = "username";
$sqlpass = "password";
$sqldbname = "ProjectSpyder";
$sqlhost = "localhost";
?>
```
You need to replace username with the username of the MySQL Server. Then do the same for the password.
The dbname parameter defines the name of the Database in the MySQL Server.
If you don't have one already, leave it at its default value.
Please ensure its possible for the user to log in and modify everything within the database.

The following lines should be executed within the MySQL shell to setup the MySQL Server.
```
create database ProjectSpyder;
use ProjectSpyder;
(unfinished, more lines will be added soon)
```

## How to install clients

Add a file named `WifiCredentials.h` inside the folder `Arduino`. Put these contents inside it:
```
const char * ssid = "WIFISSID";
const char * password = "WIFIPASSWORD";
const char * serverhostname = "SERVERHOSTNAMEORIPADDRESS";
```
