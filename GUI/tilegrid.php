<?php 
require_once("system.php");
if (!sessionvalid()) die("INVALIDSESSION");

$devices = getdevices();

function gettile($device) {
	//gettile: needs to output the data userfriendly for the GUI
	$data = getdata($device);
	$returnstring = "<table>";
	foreach ($data["data"] as $datafield) {
		$returnstring = $returnstring."<tr>";
		$returnstring = $returnstring."<td>".sanitizehtml($data["friendy"]["datavar"][$datafield] ?? $datafield)."</td>";
		$returnstring = $returnstring."<td>".sanitizehtml($data["friendy"]["datavalue"][$datafield] ?? $data["data"][$datafield])."</td>";
		$returnstring = $returnstring."</tr>";
	}
	$returnstring = $returnstring."</table>";
	return $returnstring;
}

?>

<div class="tilegrid">
	
	<?php 
	foreach ($devices as $device) {
		?>
		<div class="tile">
			<h1><?php echo (empty($device["name"]) ? ($friendlytypenames[$device["type"]] ?? $device["type"])." ".$device["id"] : $device["name"]);?></h1>
			<?php echo gettile($device); ?>
		</div>
		<?php
	}
	?>
	
</div>