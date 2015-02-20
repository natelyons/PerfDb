<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of util
 *
 * @author nlyons
 */

require_once('db.inc');
//require_once('usersession.class.php');
//require_once('user.class.php');

class util
{
	
	
	public static function alert ($msg)
	{
    	print "<script type='text/javascript'> alert('".$msg."'); </script>";
	}
	
	public static function confirm ($msg)
	{
    	print "<script type='text/javascript'>
				var answer;
				answer = confirm('".$msg."'); 
				if(!answer){ history.back(); }
			   </script>";
	}
	
	public static function error ($msg)
	{
		$error = $msg;
		print "<script type='text/javascript'> alert('".$error."'); history.back(); </script>";
		die();
	}
	
	public static function back ()
	{
		print "<script type='text/javascript'> history.back(); </script>";
		//die();
	}
	
	//converts a date to a short date (m/d)
	public static function toShortDate($Date)
	{
		$shortdate = util::toDbDate($Date);
		$timestamp = strtotime($shortdate);
		$shortdate = date('n\/j', $timestamp);
		return $shortdate;
	}
	
	//converts a mysql style datetime to a traditional mm/dd/yyyy formatted date (without the time portion)
	public static function toNormalDate($Date)
	{
		$timestamp = strtotime($Date);
		$normDate = date('m\/d\/Y', $timestamp);
		return $normDate;
	}
	
	//takes a mysql style datetime (yyyy-mm-dd hh:mm:ss) and returns just the 2 digit hour portion (hh)
	public static function to2DigitHour($DateTime)
	{
		$timestamp = strtotime($DateTime);
		$hour = date('H', $timestamp);
		return $hour;
	}
	
	//takes a mysql style datetime (yyyy-mm-dd hh:mm:ss) and returns just the 2 digit minute portion (mm)
	public static function to2DigitMinute($DateTime)
	{
		$timestamp = strtotime($DateTime);
		$minute = date('i', $timestamp);
		return $minute;
	}
	
	//2007-06-08 18:00:00
	//takes a mysql style datetime and returns just the time portion
	public static function toShortTime($strMysqlDateTime)
	{
		$time = '';
		if (strlen($strMysqlDateTime) != 19){
			$time = 'invalid datetime input';
		}else{
			$hour = substr($strMysqlDateTime, 11, 2);
			$minute = substr($strMysqlDateTime, 14, 2);
			if ($minute == '00'){
				$time = date('ga', mktime(intval($hour), intval($minute), 0, 1, 1, 1900));
			}else{			
				$time = date('g:ia', mktime(intval($hour), intval($minute), 0, 1, 1, 1900));
			}
		}
		return $time;		
	}	
	
	//takes a month and year as integers and adds a number of months.  it returns month year in the format: m-yyyy
	public static function month_add($intStartMonth, $intStartYear, $intMonthsToAdd){
		$newMonth = $intStartMonth + $intMonthsToAdd;
		$newYear = $intStartYear;
		while ($newMonth > 12) {
			$newMonth = $newMonth - 12;
			$newYear++;
		}
		$monthYear = $newMonth . '-' . $newYear;
		return $monthYear;
	}

	//takes tab delimited contents of a textarea where each line is seperated with a return character and creates an array
	public static function textAreaToArray($contents)
	{
		$contents = str_replace("\r\n", "##", $contents);
		$contents = str_replace("\n\n", "##", $contents);
		$contents = str_replace("\t", "||", $contents);
		$arrMyArray = explode("##", $contents);	
		return $arrMyArray;
	}

	//make string safe...use to recieve user input
	public static function cleanString ($string)
	{
			 //$string = strip_tags($string, '<b><i><p><br>');
			 if (util::foundSIChars($string) == true || util::foundXSSChars($string) == true){
			 	util::banIP($_SERVER['REMOTE_ADDR'], 'CI or XSS');
				util::logActivity('Suspicious input was recieved and computer was banned. IPAddress: ' . $_SERVER['REMOTE_ADDR'] . ' : ' . $string);
				//util::alert('Your activity has been deemed suspicous and has been logged for review.  An administrator has been notified');
				//util::redirect('banned.php');
			 }
			 $string = addslashes($string);
			 return $string;
	
	}
	
	function stripslashes_deep ($text, $times) {
		$i = 0;
		
		// loop will execute $times times.
		while (strstr($text, '\\') && $i != $times) {
			$text= stripslashes($text);
			$i++;
		}
		
		return $text;
	}

	//check email format function
	public static function CheckEmailFormat($Email) 
	{	
			if (!eregi("^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$", $Email)) {
				  $result = false;
				  return $result;
			}else{
				  $result = true;
				  return $result;
			}
	}
	
	
	//convert a date with slashes (i.e. 5/01/2005) to a db date (i.e. 2005-05-01)
	public static function toDbDate($strDate)
	{
		$year = '0000';
		$month = '00';
		$day = '00';
		if (substr_count($strDate, '-') > 0){
			$arrDateParts = explode('-', $strDate);
			$year = $arrDateParts[0];
			$month = $arrDateParts[1];
			$day = $arrDateParts[2];
		}else{
			$arrDateParts = explode('/', $strDate);
			$month = $arrDateParts[0];
			$day = $arrDateParts[1];
			$year = $arrDateParts[2];
		}
		//format month
		if ($month < 10 && strlen($month) < 2){
			$month = 0 . $month;
		}
		
		//format day
		if ($day < 10 && strlen($day) < 2){
			$day = 0 . $day;
		}
		
		//format year
		if (strlen($year) == 2){
			if (date("y") - $year >= 0){
				$year = 20 . $year;
			}else{
				$year = 19 . $year;
			}	
		}	
		
		//check the date
		if (checkdate($month, $day, intval($year)) == true){
			$formattedDate = $year . '-' . $month . '-' . $day;
			return $formattedDate;
		}else{
			return '0000-00-00';
		}
	}

	//redirects current page to designated $URL
	public static function redirect($URL){
		//util::alert("Redirecting to: $URL.");
		print "<script type=\"text/javascript\">";
		print "window.location.href = '$URL'";
		print "</script>";
	}
	
	//redirects current page to designated $URL
	public static function redirectTop($URL){
		//util::alert("Redirecting to: $URL.");
		print "<script type=\"text/javascript\">";
		print "top.location.href = '$URL'";
		print "</script>";
	}
	
	//user signout
	public static function SignOut($url = ""){
		unset($_SESSION['LoggedIn']);
		unset($_SESSION['Email']);
		unset($_SESSION['URL']);
		if($url <> "")
		{
			util::redirectTop($url);
		} else {
			util::redirectTop("index.php");
		}
	}//end signout for user
	
	//function to convert empty strings to an html space to make tables look better
	public static function emptyToSpace($myString)
	{
		if ($myString == ""){
		$myString = "&nbsp;";
	}
	return $myString;
	}//end function emptyToSpace
	
	
	//returns the diff in seconds of 2 timestamps use with time()
	public static function getTimeDiff($intStartTime, $intEndTime)
	{
		$intSeconds = $intEndTime - $intStartTime;
		return $intSeconds;
	}
	
	/*public static isValid($arrFields, $arrValues)
	{
		//Validation
		$message = "<span class='failMsg'>Error! </span>The following fields are required and cannot be left blank";
		$Valid = true;
		$i = 0;
		while($i <= count($arrFields))
		{
			if ($arrValues[$i] == "") 
			{ 
				$message .= " - ".$arrFields[$i]; 
				$this->Valid = false; 
				echo($arrFields[$i]." blank.<br>");
			}
			$i++;
		}
		$message .= ".";
		if(!$Valid) { $_SESSION['UserMessage'] = $message; } else { $_SESSION['UserMessage'] = ""; }
		return $Valid;
	}*/
	
	
	
	//takes any url string as a parameter and looks for http:.  If it finds it, it replaces it with https and returns the string
	public static function forceSSL($url)
	{
		$newUrl = $url;
		if (stristr($url, 'http:')){
			$newURL = str_replace('http:', 'https:', $url);
		}
		return $newUrl;
	}
	
	//takes any url string as a parameter and looks for https:.  If it finds it, it replaces it with http and returns the string
	public static function forceHttp($url)
	{
		$newUrl = $url;
		if (stristr($url, 'https:')){
			$newURL = str_replace('https:', 'http:', $url);
		}
		return $newUrl;
	}
	
	public static function curPageURL() 
	{
		$pageURL = 'http';
		if ($_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
		$pageURL .= "://";
		if ($_SERVER["SERVER_PORT"] != "80") {
			$pageURL .= $_SERVER["SERVER_NAME"].":".$_SERVER["SERVER_PORT"].$_SERVER["REQUEST_URI"];
		} else {
			$pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];
		}
		return $pageURL;
	}
	
	public static function curPageName() 
	{
 		return substr($_SERVER["SCRIPT_NAME"],strrpos($_SERVER["SCRIPT_NAME"],"/")+1);
	}
	
	public static function subdomainPrefix()
	{
		$domain = '.myshoeshoppe.com/';
		$http = 'http://';
		$https = 'https://';
		$url = strrpos(util::curPageURL(), $https);
		if($url === false)
		{
			$url = substr(util::curPageURL(), strlen($http));
		} else {
			$url = 	substr(util::curPageURL(), strlen($https));
		}
		$prefix = substr($url, 0, strlen($url) - strlen($domain));
		return $prefix;
	}
	
	public static function subdomainPrefix2()
	{
		$prefix = '';
		//strip http part off
		$url = util::curPageURL();
		util::alert($url);
		$arrSplit1 = explode('//', $url);
		$url = $arrSplit1[1];
		util::alert($url);
		//find the subdomain portion
		$arrSplit2 = explode('.', $url);
		$i = 0;
		$bDomainFound = false;
		while($bDomainFound == false){
			if(stristr($arrSplit2[$i], 'myshoeshoppe.com')){
				$prefix = $arrSplit2[$i - 1];
				$bDomainFound = true;
			}else{
				$i++;
			}
		}
		return $prefix;
	}

	public static function generatePassword ($length = 12)
	{		
	  // start with a blank password
	  $password = "";
	
	  // define possible characters
	  $possible = "0123456789bcdfghjkmnpqrstvwxyz"; 
		
	  // set up a counter
	  $i = 0; 
		
	  // add random characters to $password until $length is reached
	  while ($i < $length) 
	  {
		// pick a random character from the possible ones
		$char = substr($possible, mt_rand(0, strlen($possible)-1), 1);
			
		// we don't want this character if it's already in the password
		if (!strstr($password, $char)) { 
		  $password .= $char;
		  $i++;
		}	
	  }
	
	  // done!
	  return $password;
	}//random password generator
	
	public static function generateRandomString ($length, $intCharSet)
	{	
	  //if length not given, assume 10
	  if ($length == 0){
		$length = 10;  
	  }
	  // start with a blank password
	  $password = "";
	
	  // define possible characters
	  switch ($intCharSet){
			case 0: $possible = "0123456789abcdfghjkmnpqrstvwxyz";  break;
			case 1: $possible = '0123456789abcdfghjkmnpqrstvwxyz!@#$%^&*()_-+'; break;
		}
		
	  // set up a counter
	  $i = 0; 
		
	  // add random characters to $password until $length is reached
	  while ($i < $length) 
	  {
		// pick a random character from the possible ones
		$char = substr($possible, mt_rand(0, strlen($possible)-1), 1);
			
		// we don't want this character if it's already in the password
		if (!strstr($password, $char)) { 
		  $password .= $char;
		  $i++;
		}	
	  }
	
	  // done!
	  return $password;
	}

	
	
	public static function ipOk($strIP)
	{
		$db = new db();
		if ($db->exists('bannedips', 'IpAddress', $strIP) == true){
			return false;
		}else{
			return true;
		}
	}
	
	public static function foundSIChars($string)
	{
		$arrImmediateBan = array('where 1=1');
		$arrTwoOrMoreBan = array('--', ';', 'where', 'select', 'drop', 'from', 'declare', '1=1', "'", 'execute', '/*');
		$countIB = 0;		
		$countTOMB = 0;
		$originalString = $string;
		
		foreach($arrImmediateBan as $strCS){
			if (stristr($string, $strCS) != false){
				str_ireplace($strCS, '', $string);
				$countIB++;
			}
		}
		foreach($arrTwoOrMoreBan as $strCS){
			if (stristr($string, $strCS) != false){				
				if ($countTOMB > 0){str_ireplace($strCS, '', $string);}
				$countTOMB++;
			}
		}
		if ($countIB > 0 || $countTOMB > 1){
			return true;
		}else if ($countTOMB == 1){
			//not enough to ban, but log activity anyway
			util::logActivity('Somewhat suspicious input was recieved from IPAddress: ' . $_SERVER['REMOTE_ADDR'] . ' : ' . $originalString);
			return false;
		}else{
			return false;
		}
		
	}
	
	public static function foundXSSChars($string)
	{
		$arrImmediateBan = array("alert('");
		$arrTwoOrMoreBan = array('java', 'script');
		$countIB = 0;		
		$countTOMB = 0;
		
		foreach($arrImmediateBan as $strCS){
			if (stristr($string, $strCS) != false){
				str_ireplace($strCS, '', $string);
				$countIB++;
			}
		}
		foreach($arrTwoOrMoreBan as $strCS){
			if (stristr($string, $strCS) != false){				
				if ($countTOMB > 0){str_ireplace($strCS, '', $string);}
				$countTOMB++;
			}
		}
		if ($countIB > 0 || $countTOMB > 1){
			return true;
		}else if ($countTOMB == 1){
			//not enough to ban, but log activity anyway
			util::logActivity('Somewhat suspicious input was recieved from IPAddress: ' . $_SERVER['REMOTE_ADDR'] . ' : ' . $originalString);
			return false;
		}else{
			return false;
		}
	}
	
	public static function banIP($strIP, $strBanType)
	{
		$db = new db();
		$sql = "insert into bannedips (IpAddress, DateBanned, TypeOfBan) values('$strIP',  NOW(), '$strBanType')";
		$db->run($sql);		
	}
	
	public static function logActivity($strLogEntry)
	{
		$strLogEntry = date('Y-m-d H:i:s') . ' - ' . $strLogEntry;
		$intPointer = fopen('..\includes\activityLog.txt', 'ab');
		fwrite($intPointer, "\n" . $strLogEntry);
		fclose($intPointer);
	}
	
	public static function logProblem($strLogEntry)
	{
		$strLogEntry = date('Y-m-d H:i:s') . ' - ' . $_SERVER['REMOTE_ADDR'] . ' - ' . $strLogEntry;
		$intPointer = fopen('/home2/myshoesh/public_html/MSSDEV/includes/problemLog.txt', 'ab');
		fwrite($intPointer, "\n" . $strLogEntry . "\n");
		fwrite($intPointer, util::parse_backtrace(debug_backtrace()) . "=======================================================\n");
		fclose($intPointer);
		return(' - Issue Logged - ');
	}
	
	public static function logTraceInfo($strLogEntry)
	{
		$strLogEntry = date('Y-m-d H:i:s') . ' - ' . $strLogEntry;
		$intPointer = fopen('/home2/myshoesh/public_html/MSSDEV/includes/traceLog.txt', 'ab');
		fwrite($intPointer, "\n" . $strLogEntry . "\n");
		fwrite($intPointer, util::parse_backtrace(debug_backtrace()) . "=======================================================\n");
		fclose($intPointer);
	}
	
	public static function logTxInfo($strLogEntry)
	{
		  $strLogEntry = date('Y-m-d H:i:s') . ' - ' . $strLogEntry;
		  $intPointer = fopen('/home2/myshoesh/public_html/MSSDEV/includes/txLog.txt', 'ab');
		  fwrite($intPointer, "\n" . $strLogEntry . "\n");
		  fwrite($intPointer, util::parse_backtrace(debug_backtrace()) . "=======================================================\n");
		  fclose($intPointer);
	}
	
	public static function parse_backtrace($raw){ 

        $output=""; 
        
        foreach($raw as $entry){ 
                $output.="\nFile: ".$entry['file']." (Line: ".$entry['line'].")\n"; 
                $output.="Function: ".$entry['function']."\n"; 
                $output.="Args: ".implode(", ", $entry['args'])."\n"; 
        } 

        return $output; 
    } 
	
	
	public static function generateDropDownOptions($arrValues, $arrOptions, $selectedValue){
		$i = 0;
		$html = '';
		foreach($arrValues as $strValue){
			$selected = '';
			if ($strValue == $selectedValue){$selected = 'selected';	}
			$html .= '
				<option value="' . $strValue . '" ' . $selected . '>' . $arrOptions[$i] . '</option>';
			$i++;
		}
		return $html;
	}
	
	public static function encryptData($value){
	   $key = 'jwse842^%7fdut26(=3@';	   
	   $text = $value;
	   $iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_128, MCRYPT_MODE_ECB);
	   $iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
	   $crypttext = mcrypt_encrypt(MCRYPT_RIJNDAEL_128, $key, $text, MCRYPT_MODE_ECB, $iv);
	   $crypttext = addslashes($crypttext);
	   return $crypttext;
	}
	
	public static function decryptData($value){
	   $key = "jwse842^%7fdut26(=3@";
	   $crypttext = $value;
	   $iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_128, MCRYPT_MODE_ECB);
	   $iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
	   $decrypttext = mcrypt_decrypt(MCRYPT_RIJNDAEL_128, $key, $crypttext, MCRYPT_MODE_ECB, $iv);
	   $crypttext = stripslashes($decrypttext);
	   return trim($decrypttext);
	}
	
	public static function start_session()
	{
		//if the page variable is set, persist the session, then insert the session ID into the database
		session_start();
		$session = new usersession(session_id());
		if(isset($_REQUEST['page']))
		{
			$session->getObject($_REQUEST['page']);
			$session->persistSession();
			$session->delete($_REQUEST['page']);
		}
		$session->createObject();
		return $session->getRandomID();
	}
	
	
}
?>
