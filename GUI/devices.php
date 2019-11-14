<?php
require_once("system.php");
global $systemname;
checksession();

$friendlytypenames = array(
	//"motor" => "Motor",
	//"lock" => "Lock",
	"addressablergbledstrip" => "LED-Strip",
	"rgbled" => "RGB-LED",
	"led" => "LED",
	//"epaper" => "E-Paper Screen",
	"button" => "Button",
	//"finger" => "Fingerprint sensor",
	//"temp" => "temperature sensor",
	//"rotation" => "rotational sensor",
	"rgbdetect" => "RGB sensor",
	"raw" => "unknown",
	"" => null,
);


?>

<html>
	<head>
		<title><?php echo $systemname;?> Devices</title>
		<style>
			body {
				background-color: black;
			}
			h1 {
				color: white;
			}
			td {
				color: white;
				border: white solid 1px;
			}
			th {
				color: white;
				border: white solid 1px;
			}
			
			nav {
				color: white;
			}
			a {
				color: white;
			}
		</style>
	</head>
	<body>
		<nav>
			<h1><?php echo $systemname;?> Devices</h1>
			<ul>
				<li><a href="main.php">Home</a></li>
				<!--<li><a href="devices.php">Devices</a></li>-->
			</ul>
		</nav>
		<table>
			<?php 
			//devices array: columns of the devices table to show. format: Visible text => column name of table devices.
			$columns = array(
				"ID" => "id",
				"Name" => "name",
				"Type" => "type",
				"IP-Address" => "ipaddress",
			);
			$devices = getdevices();
			if (sizeof($devices) == 0) {
				die("Error: No devices found.");
			}
			echo "<tr>";
			foreach ($columns as $key => $column) {
				echo "<th>";
				echo $key;
				echo "</th>";
			}
			echo "</tr>";
			foreach ($devices as $device) {
				echo "<tr>";
				foreach ($columns as $column) {
					echo "<td>";
					echo ($friendlytypenames[$device[$column]] ?? $device[$column]);
					echo "</td>";
				}
				echo "</tr>";
			}
			?>
		</table>
	</body>
</html>