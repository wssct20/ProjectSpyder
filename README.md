# ProjectSpyder
SmartHome by WSSCT20

ProjectSpyder is an smart home system build up to be easy, capable and have a wide compatibility.

__WARNING: _We are currently developing ProjectSpyder, so don't expect it to work.___

## How to set up server
The software uses the Apache2 webserver with PHP enabled and a MySQL Server.

First of, install the required programs:
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
```
sudo hostname SpyderHub
```
If you are using Raspbian, you might need to run `raspi-config` and change the hostname in there.

After that you need to setup basic settings and credentials for the MySQL Server.
To do this you need to place a file named `credentials.php` into the webroot. Don't worry, its not accessible from outside.
It needs to contain these lines:
```
<?php
$sqluser = "username";
$sqlpass = "password";
$sqldbname = "ProjectSpyder";
$sqlhost = "localhost";
?>
```
You need to replace `sqluser` with the username of the MySQL Server. Then do the same for the password.
The `sqldbname` parameter defines the name of the Database in the MySQL Server.
Please ensure its possible for the user to log in and modify everything within the database.

## How to set up and install clients

Add a file named `WifiCredentials.h` inside the folder `Arduino`. Put these contents inside it:
```
const char * ssid = "WIFISSID";
const char * password = "WIFIPASSWORD";
const char * serverhostname = "SERVERHOSTNAMEORIPADDRESS";
```
You need to replace `WIFISSID` with the SSID of your wifi network. 
Then replace `WIFIPASSWORD` with the according password.
You also need to replace `SERVERHOSTNAMEORIPADDRESS` with the server hostname or the IP Address of the server, 
if the Router is not capable of forwarding such requests. 
Most of the time the hostname will work just fine.
If you are using an IP address though, please ensure it is static.


