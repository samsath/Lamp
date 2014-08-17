<html>
<head>
<title> PHP Test Script </title>
</head>
<body>
<?PHP

$ip = @file_get_contents("http://www.apps-tube.com/apps/ip-address/ip.php");

echo $ip;

?>
</body>
</html> 
