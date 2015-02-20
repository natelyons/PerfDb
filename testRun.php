<?php
//error_reporting(E_ALL);
//ini_set("display_errors", 1);

require_once './includes/db.inc';
require_once './includes/testrun.inc';
require_once './includes/test_run_environment.inc';
date_default_timezone_set("America/Denver"); 

$strInput = file_get_contents('php://input');
$arrInput = json_decode($strInput, true);
//print_r ($objInput);
$jsonOutput = '';

//*******************************************************
//Create a new test run record
//*******************************************************
if ($arrInput['method'] == "startNewRun"){
    
    //sample json to post to http://moab-walldisplay.ac/perfdb/testRun.php
    /*
     {
        "method": "startNewRun",
        "version":"0",
        "description": "this is a fake test run",
        "external_id": "nl_test2",
        "is_manual": "1",
        "run_by": "nlyons",
        "test_fam_id": "1"
     }
     */
    
    //create a new test run record in the database
    $objTestRun = new test_run();
    $objTestRun->setVersion(mysql_real_escape_string($arrInput['version']));
    $objTestRun->setDescription(mysql_real_escape_string($arrInput['description']));
    $objTestRun->setDuration(-1); //duration gets set to -1 on create.  It will be calculated on test run completion
    //$objTestRun->setEnd_date('');
    $objTestRun->setExternal_id(mysql_real_escape_string($arrInput['external_id']));
    $objTestRun->setIs_manual(mysql_real_escape_string($arrInput['is_manual']));
    $objTestRun->setRun_by(mysql_real_escape_string($arrInput['run_by']));
    $objTestRun->setStart_date(date("Y-m-d H:i:s"));
    $objTestRun->setTest_fam_id(mysql_real_escape_string($arrInput['test_fam_id']));
    
    $intTestRunId = $objTestRun->createObject();
    //echo('timestamp = ' . $objTestRun->getStart_date() . '<br>')
    
    //Return json status of operation
    $jsonOutput = array("status" => 1, "msg" => "attempted to create a new test run", "test_run_id" => $intTestRunId); //if the test_run_id is null, that means the record could not be created.
   
    
    
    
//*********************************************************
//Describe a test run environment
//*********************************************************    
}elseif ($arrInput['method'] == "describeEnvironment"){
    
 //sample json to post
   /*
    {  
        "method": "describeEnvironment",
        "test_run_id":"3",
        "property_values":
        {  
           "0":{  
              "environment_property":"torque_server_name",
              "value":"qt23.ac"
           },
           "1":{  
              "environment_property":"moab_server_name",
              "value":"qt30.ac"
           },
            "2":{  
              "environment_property":"torque_server_memory",
              "value":"16"
           },
            "3":{  
              "environment_property":"moab_server_memory",
              "value":"32"
           },
            "4":{  
              "environment_property":"moab_server_cores",
              "value":"16"
           },
            "5":{  
              "environment_property":"torque_server_cores",
              "value":"12"
           }
        }
    }
    */
    $i = 0;
    $objTRE = new test_run_environment();
    $objTRE->setTest_run_id($arrInput['test_run_id']);
    foreach ($arrInput['property_values'] as $pv){
        $objTRE->setEnvironment_property($pv['environment_property']);
        $objTRE->setProperty_value($pv['value']);
        $objTRE->createObject();
        $i++;
    }
    
    
    $jsonOutput = array("test_run_id" => $arrInput['test_run_id'], "tr_env_records_created" => $i);



//*********************************************************
//End an existing test run
//*********************************************************    
}elseif ($arrInput['method'] == "endTestRun"){
    
    //sample json to post to http://moab-walldisplay.ac/perfdb/testRun.php
    /*
     {
        "method": "endTestRun",
        "tr_id": "9",
        "clean_end":"1"
     }
     */
    
    //update an existing test_run record with and end_datetime and duration.
    $objTestRun = new test_run();
    $objTestRun->getObject(mysql_real_escape_string($arrInput['tr_id']));
    $objTestRun->setClean_end(mysql_real_escape_string($arrInput['clean_end']));
    $objTestRun->setEnd_date(date("Y-m-d H:i:s"));
    
    $objTestRun->endRun();
    //echo('timestamp = ' . $objTestRun->getStart_date() . '<br>')
    
    //Return json status of operation
    $jsonOutput = array("status" => 1, "msg" => "attempted to end test run", "test_run_id" => $objTestRun->getId(), "duration" => $objTestRun->getDuration()); 
    
    
}else{
    $jsonOutput = array("status" => 0 , "msg" => "Request method not accepted", "method_called" => $objInput->{'method'});
}




header('Content-type: application/json');
echo json_encode($jsonOutput);


?>


