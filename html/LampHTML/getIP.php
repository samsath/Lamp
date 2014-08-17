<?php
/* getip.php */


$ip=$_SERVER['REMOTE_ADDR'];

print json_encode(array('ip' => $ip));
?>
