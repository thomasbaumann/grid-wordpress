<?php

include 'classes/bootstrap.php';

$storage=new griddb();
if(isset($_REQUEST['path']) && $_REQUEST['path']=='/ajax')
{
	$storage->handleAjaxCall();
	return;
}
?>
<html>
<head>
</head>
<body>
<?php
$grid=$storage->loadGrid(1);
$output=$grid->render(false);
echo $output;
?>
</body>
</html>
