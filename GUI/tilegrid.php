<?php 
require_once("system.php");
if (!sessionvalid()) die("INVALIDSESSION");

include_once("specific.php");

$devices = getdevices();
?>

<div class="tilegrid">
	
	<?php 
	foreach ($devices as $device) {
		?>
		<div class="tile">
			<h1><?php echo (empty($device["name"]) ? $device["type"]." ".$device["id"] : $device["name"]);?></h1>
			<p><?php echo gettile($device["type"], getdata($device["id"])); ?></p>
		</div>
		<?php
	}
	?>
	
</div>