<?php 
require_once("system.php");
if (!sessionvalid()) die("INVALIDSESSION");

$devices = getdevices();
?>

<div class="tilegrid">
	
	<?php 
	foreach ($devices as $device) {
		?>
		<div class="tile">
			<h1><?php echo (empty($device["name"]) ? ($friendlytypenames[$device["type"]] ?? $device["type"])." ".$device["id"] : $device["name"]);?></h1>
			<?php echo gettile($device["type"], getdata($device["id"])); ?>
		</div>
		<?php
	}
	?>
	
</div>