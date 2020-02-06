<?php 
//this is the main screen of the gui

require_once("system.php");
global $systemname;

checksession();

?>

<!DOCTYPE html>
<html lang="de">
	<head>
        <meta charset="utf-8">
		<title><?php echo $systemname;?></title>
        <link rel="stylesheet" href="style.css">
        <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
        <link href="https://fonts.googleapis.com/css?family=Roboto+Condensed&display=swap" rel="stylesheet"> 
		<style>
			input {
			    color: white;
			    background-color: black;
			}
		</style>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
		<script>
			async function refreshmainframe() {
				$.ajax({
					url: "tilegrid.php",
					success: function(data) {
						document.getElementById("mainframe").innerHTML = data;
					},
					dataType: "html"
				});
			}
			var refreshhandler = setInterval(refreshmainframe, 5000);
		</script>
	</head>
	<body>
		<nav>
			<h1><a href="main.php">ProjectSpyder</a></h1>
			<ul>
                <div class="separator"></div>
				<li><a href="devices.php">Devices</a></li>
                <div class="separator"></div>
				<li><a href="usermanagement.php">Usermanagement</a></li>
			</ul>
			<ul>
				<li class="bordered">
					<form action="login.php" method=post>
						<input type=text name=action value=logout style="display: none;">
						<input type=submit name=submit value=Logout>
					</form>
				</li>
			</ul>
		</nav>
		
		<div id=mainframe></div>
	</body>
<html>