<?php
// mana 2008.10.10-
if($_SERVER["HTTP_HOST"] === "localhost"){
define("HOME_DIR", "C:/MY_WINDOWS_DOCROOT");
define("DOCROOT", "http://localhost/XAMPP_DOCROOT");
} else {
define("HOME_DIR", "/home/MYHOME");
define("DOCROOT", "http://my.server/");
	
}
define("CONF_DIR", HOME_DIR."/conf");
define("CLASS_DIR", HOME_DIR.'/class');
define("DOCROOT_DIR", HOME_DIR."/public_html");
define("BIN_DIR", HOME_DIR."/bin");

define("TMP_DIR", HOME_DIR."/tmp");
define("TMP_IMG_DIR", HOME_DIR."/public_html/tmp_img");
define("TMP_IMG_URL", DOCROOT."tmp_img");

?>