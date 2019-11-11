<?php
require_once("system.php");
checksession();

?>

<html>
	<head>
		<title>ProjectSpyder Devices</title>
		<style>
			body {
				background-color: black;
			}
			h1 {
				color: white;
			}
		</style>
	</head>
	<body>
		<h1>ProjectSpyder Devices</h1>
		
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
					echo $device[$column];
					echo "</td>";
				}
				echo "</tr>";
			}
			?>
		</table>
	</body>
</html>