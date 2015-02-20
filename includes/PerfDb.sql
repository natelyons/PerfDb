/*
 Navicat MySQL Data Transfer

 Source Server         : Wall Dislpay
 Source Server Type    : MySQL
 Source Server Version : 50173
 Source Host           : localhost
 Source Database       : PerfDb

 Target Server Type    : MySQL
 Target Server Version : 50173
 File Encoding         : utf-8

 Date: 02/20/2015 14:21:00 PM
*/

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
--  Table structure for `environment_property`
-- ----------------------------
DROP TABLE IF EXISTS `environment_property`;
CREATE TABLE `environment_property` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `version` int(11) NOT NULL,
  `description` varchar(255) NOT NULL,
  `env_component` varchar(255) NOT NULL,
  `value_type` varchar(255) NOT NULL,
  `component_property` varchar(255) NOT NULL,
  PRIMARY KEY (`id`,`component_property`)
) ENGINE=MyISAM AUTO_INCREMENT=32 DEFAULT CHARSET=latin1;

-- ----------------------------
--  Records of `environment_property`
-- ----------------------------
BEGIN;
INSERT INTO `environment_property` VALUES ('2', '0', 'Version of Torque used during the test', 'Torque', 'string', 'torque_version'), ('3', '0', 'Name of server used for Torque', 'Torque', 'string', 'torque_server_name'), ('4', '0', 'Amount of memory on Torque server (GB)', 'Torque', 'integer', 'torque_server_memory'), ('5', '0', 'Number of processor cores on Torque server (no hyperthreading)', 'Torque', 'integer', 'torque_server_cores'), ('7', '0', 'Are MOMs being run locally on Torque server', 'Torque', 'boolean', 'torque_server_has_local_moms'), ('8', '0', 'Is Torque using multi-moms for the test', 'Torque', 'boolean', 'torque_using_multi_mom'), ('6', '0', 'Is hyper-threading turned on for Torque server', 'Torque', 'boolean', 'torque_server_ht'), ('1', '0', 'Moab and Torque are on the same server for the test', 'Torque', 'boolean', 'torque_on_moab_server'), ('9', '0', 'How many total MOMs are reporting to Torque', 'Torque', 'integer', 'torque_total_moms'), ('10', '0', 'Across how many servers are MOMs divided', 'Torque', 'integer', 'torque_num_mom_servers'), ('11', '0', 'Version of Moab used during the test', 'Moab', 'string', 'moab_version'), ('12', '0', 'Name of server used for Moab', 'Moab', 'string', 'moab_server_name'), ('13', '0', 'Amount of memory on Moab server (GB)', 'Moab', 'integer', 'moab_server_memory'), ('14', '0', 'Number of processor cores on Moab server (no hyperthreading)', 'Moab', 'integer', 'moab_server_cores'), ('15', '0', 'Is hyper-threading turned on for Moab server', 'Moab', 'boolean', 'moab_server_ht'), ('17', '0', 'Was Moab built with optimizations on or left off or turned on for more debugging', 'Moab', 'boolean', 'moab_with_optimizations'), ('18', '0', 'Moab log level during test', 'Moab', 'integer', 'moab_log_level'), ('19', '0', 'Was Moab writing to the Insight event queue', 'Moab', 'boolean', 'moab_writing_to_insight'), ('20', '0', 'Was Moab writing to MongoDB', 'Moab', 'boolean', 'moab_writing_to_mongo'), ('21', '0', 'Was Moab Using ODBC', 'Moab', 'boolean', 'moab_using_odbc'), ('22', '0', 'Was Moab part of a Grid', 'Moab', 'boolean', 'moab_in_grid'), ('16', '0', 'Moab.cfg file location or key config parameters used', 'Moab', 'string', 'moab_config_params'), ('23', '0', 'Primary resource manager being used by Moab', 'Moab', 'string', 'moab_pri_rm'), ('24', '0', 'Was Insight installed on the same server as Moab', 'Insight', 'boolean', 'insight_on_moab_server'), ('25', '0', 'Amount of memory on Insight server (GB)', 'Insight', 'integer', 'insight_server_memory'), ('26', '0', 'Version of Insight used during test', 'Insight', 'string', 'insight_version'), ('27', '0', 'Name of server used for Insight', 'Insight', 'string', 'insight_server_name'), ('28', '0', 'Number of processor cores on Insight server (no hyperthreading)', 'Insight', 'integer', 'insight_server_cores'), ('29', '0', 'Is hyper-threading turned on for Insight server', 'Insight', 'boolean', 'insight_server_ht'), ('30', '0', 'GHz per proc on Insight server', 'Insight', 'double', 'insight_ghz_per_proc'), ('31', '0', 'GHz per proc on Torque server', 'Torque', 'double', 'torque_ghz_per_proc');
COMMIT;

-- ----------------------------
--  Table structure for `metric`
-- ----------------------------
DROP TABLE IF EXISTS `metric`;
CREATE TABLE `metric` (
  `id` int(11) NOT NULL,
  `version` int(11) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `max_double` double DEFAULT NULL,
  `max_integer` int(11) DEFAULT NULL,
  `min_double` double DEFAULT NULL,
  `min_integer` int(11) DEFAULT NULL,
  `metric_name` varchar(255) NOT NULL,
  `value_type` varchar(255) NOT NULL,
  `url` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
--  Records of `metric`
-- ----------------------------
BEGIN;
INSERT INTO `metric` VALUES ('9', '0', 'Number of jobs per second that can be added to the queue', '-1', '-1', '0', '0', 'QSub Job Injection Rate - Min', 'integer', null), ('10', '0', 'Number of jobs per second that can be added to the queue', '-1', '-1', '0', '0', 'QSub Job Injection Rate - Median', 'integer', null), ('11', '0', 'Number of jobs per second that can be added to the queue', '-1', '-1', '0', '0', 'QSub Job Injection Rate - Mean', 'integer', null), ('12', '0', 'Number of jobs per second that can be added to the queue', '-1', '-1', '0', '0', 'QSub Job Injection Rate - Max', 'integer', null), ('18', '0', 'Number of jobs started per second', '-1', '-1', '0', '0', 'Job Start Rate - Min', 'integer', null), ('1', '0', 'Schedule Duration is the time required to complete one scheduling iteration in Moab', '-1', '-1', '0', '0', 'Schedule Duration - Min', 'double', null), ('2', '0', 'Schedule Duration is the time required to complete one scheduling iteration in Moab', '-1', '-1', '0', '0', 'Schedule Duration - Min', 'double', null), ('19', '0', 'Number of jobs started per second', '-1', '-1', '0', '0', 'Job Start Rate - Median', 'integer', null), ('20', '0', 'Number of jobs started per second', '-1', '-1', '0', '0', 'Job Start Rate - Mean', 'integer', null), ('21', '0', 'Number of jobs started per second', '-1', '-1', '0', '0', 'Job Start Rate - Max', 'integer', null), ('17', '0', '?', '-1', '-1', '0', '0', 'RM Node Load - Pct of Iteration', 'percentage', null), ('26', '0', '?', '-1', '-1', '0', '0', 'RM Job Load - Pct of Iteration', 'percentage', null), ('3', '0', 'Schedule Duration is the time required to complete one scheduling iteration in Moab', '-1', '-1', '0', '0', 'Schedule Duration - Min', 'double', null), ('4', '0', 'Schedule Duration is the time required to complete one scheduling iteration in Moab', '-1', '-1', '0', '0', 'Schedule Duration - Min', 'double', null), ('5', '0', 'Throughput Rate is how fast jobs are getting all the way through the system, assuming instantly completing jobs', '-1', '-1', '0', '0', 'Throughput Rate - Min', 'double', null), ('8', '0', 'Throughput Rate is how fast jobs are getting all the way through the system, assuming instantly completing jobs', '-1', '-1', '0', '0', 'Throughput Rate - Max', 'double', null), ('7', '0', 'Throughput Rate is how fast jobs are getting all the way through the system, assuming instantly completing jobs', '-1', '-1', '0', '0', 'Throughput Rate - Mean', 'double', null), ('6', '0', 'Throughput Rate is how fast jobs are getting all the way through the system, assuming instantly completing jobs', '-1', '-1', '0', '0', 'Throughput Rate - Median', 'double', null), ('13', '0', '?', '-1', '-1', '0', '0', 'RM Node Load - Min', 'double', null), ('14', '0', '?', '-1', '-1', '0', '0', 'RM Node Load - Median', 'double', null), ('15', '0', '?', '-1', '-1', '0', '0', 'RM Node Load - Mean', 'double', null), ('16', '0', '?', '-1', '-1', '0', '0', 'RM Node Load - Max', 'double', null), ('22', '0', '?', '-1', '-1', '0', '0', 'RM Job Load - Min', 'double', null), ('23', '0', '?', '-1', '-1', '0', '0', 'RM Job Load - Median', 'double', null), ('24', '0', '?', '-1', '-1', '0', '0', 'RM Job Load - Mean', 'double', null), ('25', '0', '?', '-1', '-1', '0', '0', 'RM Job Load - Max', 'double', null);
COMMIT;

-- ----------------------------
--  Table structure for `test_execution`
-- ----------------------------
DROP TABLE IF EXISTS `test_execution`;
CREATE TABLE `test_execution` (
  `id` bigint(11) NOT NULL AUTO_INCREMENT,
  `version` int(11) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `duration` int(11) DEFAULT NULL,
  `end_date` timestamp NULL DEFAULT NULL,
  `external_id` varchar(255) DEFAULT NULL,
  `result` varchar(255) NOT NULL,
  `start_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `test_run_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- ----------------------------
--  Records of `test_execution`
-- ----------------------------
BEGIN;
INSERT INTO `test_execution` VALUES ('1', '0', 'a test is being executed', '-1', null, 'testid_xvii', '', '2015-02-02 17:34:57', '7'), ('2', '0', 'a test is being executed', '-1', null, 'testid_xvii', '', '2015-02-02 17:35:00', '7'), ('3', '0', 'a test is being executed', '2', '2015-02-05 11:12:35', 'testid_xvii', '1', '2015-02-02 17:35:03', '7');
COMMIT;

-- ----------------------------
--  Table structure for `test_execution_metric`
-- ----------------------------
DROP TABLE IF EXISTS `test_execution_metric`;
CREATE TABLE `test_execution_metric` (
  `id` bigint(11) NOT NULL AUTO_INCREMENT,
  `metric_id` int(11) NOT NULL,
  `metric_value` varchar(255) DEFAULT NULL,
  `test_execution_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

-- ----------------------------
--  Records of `test_execution_metric`
-- ----------------------------
BEGIN;
INSERT INTO `test_execution_metric` VALUES ('1', '3', '15.3', '3'), ('2', '4', '.54', '3'), ('3', '3', '15.3', '3'), ('4', '4', '.54', '3');
COMMIT;

-- ----------------------------
--  Table structure for `test_family`
-- ----------------------------
DROP TABLE IF EXISTS `test_family`;
CREATE TABLE `test_family` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `info_link` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- ----------------------------
--  Records of `test_family`
-- ----------------------------
BEGIN;
INSERT INTO `test_family` VALUES ('1', 'Insight Scale Test', null, null), ('2', 'Torque High Throughput', null, null), ('3', 'Torque Stress Test', null, null);
COMMIT;

-- ----------------------------
--  Table structure for `test_run`
-- ----------------------------
DROP TABLE IF EXISTS `test_run`;
CREATE TABLE `test_run` (
  `id` bigint(11) NOT NULL AUTO_INCREMENT,
  `version` int(11) NOT NULL,
  `description` varchar(255) NOT NULL,
  `duration` varchar(30) DEFAULT NULL,
  `end_date` timestamp NULL DEFAULT NULL,
  `external_id` varchar(255) DEFAULT NULL,
  `is_manual` tinyint(1) NOT NULL,
  `run_by` varchar(255) NOT NULL,
  `start_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `clean_end` tinyint(1) DEFAULT NULL,
  `test_fam_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

-- ----------------------------
--  Records of `test_run`
-- ----------------------------
BEGIN;
INSERT INTO `test_run` VALUES ('1', '0', 'This is a fake run', '00:22:34:56', '2015-01-30 16:29:45', 'nl_test1', '1', 'nlyons', '2014-12-29 17:54:49', '1', '3'), ('2', '0', 'This is a fake run', '-1', '0000-00-00 00:00:00', 'nl_test1', '1', 'nlyons', '2015-01-23 17:54:53', null, '3'), ('3', '0', 'This is a fake run', '06:22:27:58', '2015-01-30 16:25:33', 'nl_test1', '1', 'nlyons', '2015-01-23 17:57:35', '1', '3'), ('4', '0', '\"this_is_a_description\"', '-1', '0000-00-00 00:00:00', '15', '1', 'nlyons', '2015-01-27 20:12:23', null, '2'), ('5', '0', 'this is a json fake run', '-1', '0000-00-00 00:00:00', '', '1', 'nlyons', '2015-01-29 15:22:56', null, '2'), ('6', '0', 'this is a json fake run', '-1', '0000-00-00 00:00:00', '', '1', 'nlyons', '2015-01-29 15:23:34', null, '2'), ('7', '0', 'this is a json fake run', '-1', '0000-00-00 00:00:00', 'nl_test2', '1', 'nlyons', '2015-01-29 15:24:55', null, '1'), ('8', '0', 'this is a json fake run', '-1', '0000-00-00 00:00:00', 'nl_test2', '1', 'nlyons', '2015-01-29 15:42:06', null, '1'), ('9', '0', 'this is a fake test run', '00:19:05:26', '2015-01-30 16:25:00', 'nl_test2', '1', 'nlyons', '2015-01-29 21:19:34', '1', '1'), ('10', '0', 'this is a fake test run', '-1', '0000-00-00 00:00:00', 'nl_test2', '1', 'nlyons', '2015-02-06 16:07:19', null, '1');
COMMIT;

-- ----------------------------
--  Table structure for `test_run_environment`
-- ----------------------------
DROP TABLE IF EXISTS `test_run_environment`;
CREATE TABLE `test_run_environment` (
  `id` bigint(11) NOT NULL AUTO_INCREMENT,
  `environment_property` varchar(255) NOT NULL,
  `property_value` varchar(255) DEFAULT NULL,
  `test_run_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=84 DEFAULT CHARSET=latin1;

-- ----------------------------
--  Records of `test_run_environment`
-- ----------------------------
BEGIN;
INSERT INTO `test_run_environment` VALUES ('31', 'moab_server_name', 'qt30.ac', '4'), ('30', 'torque_server_name', 'qt23.ac', '4'), ('29', 'torque_server_cores', '12', '3'), ('28', 'moab_server_cores', '16', '3'), ('27', 'moab_server_memory', '32', '3'), ('26', 'torque_server_memory', '16', '3'), ('25', 'moab_server_name', 'qt30.ac', '3'), ('24', 'torque_server_name', 'qt23.ac', '3'), ('12', 'torque_server_name', 'qt23.ac', '1'), ('13', 'moab_server_name', 'qt30.ac', '1'), ('14', 'torque_server_memory', '16', '1'), ('15', 'moab_server_memory', '32', '1'), ('16', 'moab_server_cores', '16', '1'), ('17', 'torque_server_cores', '12', '1'), ('18', 'torque_server_name', 'qt23.ac', '2'), ('19', 'moab_server_name', 'qt30.ac', '2'), ('20', 'torque_server_memory', '16', '2'), ('21', 'moab_server_memory', '32', '2'), ('22', 'moab_server_cores', '16', '2'), ('23', 'torque_server_cores', '12', '2'), ('32', 'torque_server_memory', '16', '4'), ('33', 'moab_server_memory', '32', '4'), ('34', 'moab_server_cores', '16', '4'), ('35', 'torque_server_cores', '12', '4'), ('36', 'torque_server_name', 'qt23.ac', '5'), ('37', 'moab_server_name', 'qt30.ac', '5'), ('38', 'torque_server_memory', '16', '5'), ('39', 'moab_server_memory', '32', '5'), ('40', 'moab_server_cores', '16', '5'), ('41', 'torque_server_cores', '12', '5'), ('42', 'torque_server_name', 'qt23.ac', '6'), ('43', 'moab_server_name', 'qt30.ac', '6'), ('44', 'torque_server_memory', '16', '6'), ('45', 'moab_server_memory', '32', '6'), ('46', 'moab_server_cores', '16', '6'), ('47', 'torque_server_cores', '12', '6'), ('48', 'torque_server_name', 'qt23.ac', '7'), ('49', 'moab_server_name', 'qt30.ac', '7'), ('50', 'torque_server_memory', '16', '7'), ('51', 'moab_server_memory', '32', '7'), ('52', 'moab_server_cores', '16', '7'), ('53', 'torque_server_cores', '12', '7'), ('54', 'torque_server_name', 'qt23.ac', '8'), ('55', 'moab_server_name', 'qt30.ac', '8'), ('56', 'torque_server_memory', '16', '8'), ('57', 'moab_server_memory', '32', '8'), ('58', 'moab_server_cores', '16', '8'), ('59', 'torque_server_cores', '12', '8'), ('60', 'torque_server_name', 'qt23.ac', '9'), ('61', 'moab_server_name', 'qt30.ac', '9'), ('62', 'torque_server_memory', '16', '9'), ('63', 'moab_server_memory', '32', '9'), ('64', 'moab_server_cores', '16', '9'), ('65', 'torque_server_cores', '12', '9'), ('66', 'torque_server_name', 'qt23.ac', '10'), ('67', 'moab_server_name', 'qt30.ac', '10'), ('68', 'torque_server_memory', '16', '10'), ('69', 'moab_server_memory', '32', '10'), ('70', 'moab_server_cores', '16', '10'), ('71', 'torque_server_cores', '12', '10'), ('72', 'insight_server_name', 'qt23.ac', '7'), ('73', 'insight_server_cores', '32', '7'), ('74', 'insight_server_memory', '16', '7'), ('75', 'insight_server_name', 'qt23.ac', '8'), ('76', 'insight_server_cores', '32', '8'), ('77', 'insight_server_memory', '16', '8'), ('78', 'insight_server_name', 'qt23.ac', '9'), ('79', 'insight_server_cores', '32', '9'), ('80', 'insight_server_memory', '16', '9'), ('81', 'insight_server_name', 'qt23.ac', '10'), ('82', 'insight_server_cores', '32', '10'), ('83', 'insight_server_memory', '16', '10');
COMMIT;

-- ----------------------------
--  View structure for `v_distinct_test_family_env_no_serv_names`
-- ----------------------------
DROP VIEW IF EXISTS `v_distinct_test_family_env_no_serv_names`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `v_distinct_test_family_env_no_serv_names` AS select `tf`.`name` AS `test_family`,`tf`.`id` AS `tf_id`,count(`tr`.`id`) AS `test_run_count`,`trf`.`env_properties` AS `env_properties`,`trf`.`env_values` AS `env_values` from ((`v_tr_env_flat_no_serv_names` `trf` join `test_run` `tr` on((`trf`.`test_run_id` = `tr`.`id`))) join `test_family` `tf` on((`tr`.`test_fam_id` = `tf`.`id`))) group by `tf`.`name`,`tf`.`id`,`trf`.`env_properties`,`trf`.`env_values`;

-- ----------------------------
--  View structure for `v_tr_env_flat`
-- ----------------------------
DROP VIEW IF EXISTS `v_tr_env_flat`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `v_tr_env_flat` AS select `test_run`.`id` AS `test_run_id`,`fn_collapse_tr_env_props`(`test_run`.`id`) AS `prop_vals` from `test_run`;

-- ----------------------------
--  View structure for `v_tr_env_flat_no_serv_names`
-- ----------------------------
DROP VIEW IF EXISTS `v_tr_env_flat_no_serv_names`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `v_tr_env_flat_no_serv_names` AS select `test_run`.`id` AS `test_run_id`,`fn_collapse_tr_env_props_no_serv_names`(`test_run`.`id`) AS `env_properties`,`fn_collapse_tr_env_values_no_serv_names`(`test_run`.`id`) AS `env_values` from `test_run`;

-- ----------------------------
--  Procedure structure for `sp_collapse_tr_env_props`
-- ----------------------------
DROP PROCEDURE IF EXISTS `sp_collapse_tr_env_props`;
delimiter ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_collapse_tr_env_props`(IN tr_id int(11), INOUT prop_list varchar(4000))
BEGIN

	DECLARE v_finished INTEGER DEFAULT 0;
	DECLARE v_prop varchar(255) DEFAULT "";

	DECLARE collapse_cursor CURSOR FOR
		select distinct environment_property from test_run_environment where test_run_id = tr_id order by environment_property;


	DECLARE CONTINUE HANDLER
	FOR NOT FOUND SET v_finished =1;

	OPEN collapse_cursor;

	collapse_props: LOOP
		FETCH collapse_cursor INTO v_prop;
		IF v_finished = 1 THEN
			LEAVE collapse_props;
		END IF;
		SET prop_list = CONCAT(prop_list, v_prop, "|");
	END LOOP collapse_props;

	CLOSE collapse_cursor;
END
 ;;
delimiter ;

-- ----------------------------
--  Function structure for `fn_collapse_tr_env_props`
-- ----------------------------
DROP FUNCTION IF EXISTS `fn_collapse_tr_env_props`;
delimiter ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `fn_collapse_tr_env_props`(`tr_id` int(11)) RETURNS varchar(4000) CHARSET latin1
BEGIN

	DECLARE v_finished INTEGER DEFAULT 0;
	DECLARE v_prop varchar(255) DEFAULT "";
	DECLARE prop_list varchar(4000) DEFAULT "";

	DECLARE collapse_cursor CURSOR FOR
		select concat(environment_property, "|", property_value) as prop_list from test_run_environment where test_run_id = tr_id order by environment_property;


	DECLARE CONTINUE HANDLER
	FOR NOT FOUND SET v_finished =1;

	OPEN collapse_cursor;

	collapse_props: LOOP
		FETCH collapse_cursor INTO v_prop;
		IF v_finished = 1 THEN
			LEAVE collapse_props;
		END IF;
		SET prop_list = CONCAT(prop_list, v_prop, ",");
	END LOOP collapse_props;

	CLOSE collapse_cursor;

RETURN prop_list;
END
 ;;
delimiter ;

-- ----------------------------
--  Function structure for `fn_collapse_tr_env_props_no_serv_names`
-- ----------------------------
DROP FUNCTION IF EXISTS `fn_collapse_tr_env_props_no_serv_names`;
delimiter ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `fn_collapse_tr_env_props_no_serv_names`(`tr_id` int(11)) RETURNS varchar(4000) CHARSET latin1
BEGIN

	DECLARE v_finished INTEGER DEFAULT 0;
	DECLARE v_prop varchar(255) DEFAULT "";
	DECLARE prop_list varchar(4000) DEFAULT "";

	DECLARE collapse_cursor CURSOR FOR
		select environment_property from test_run_environment where test_run_id = tr_id and environment_property not like "%server_name%" order by environment_property;


	DECLARE CONTINUE HANDLER
	FOR NOT FOUND SET v_finished =1;

	OPEN collapse_cursor;

	collapse_props: LOOP
		FETCH collapse_cursor INTO v_prop;
		IF v_finished = 1 THEN
			LEAVE collapse_props;
		END IF;
		SET prop_list = CONCAT(prop_list, v_prop, "|");
	END LOOP collapse_props;

	CLOSE collapse_cursor;

RETURN prop_list;
END
 ;;
delimiter ;

-- ----------------------------
--  Function structure for `fn_collapse_tr_env_values`
-- ----------------------------
DROP FUNCTION IF EXISTS `fn_collapse_tr_env_values`;
delimiter ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `fn_collapse_tr_env_values`(`tr_id` int(11)) RETURNS varchar(4000) CHARSET latin1
BEGIN

	DECLARE v_finished INTEGER DEFAULT 0;
	DECLARE v_val varchar(255) DEFAULT "";
	DECLARE val_list varchar(4000) DEFAULT "";

	DECLARE collapse_cursor CURSOR FOR
		select property_value from test_run_environment where test_run_id = tr_id order by environment_property;


	DECLARE CONTINUE HANDLER
	FOR NOT FOUND SET v_finished =1;

	OPEN collapse_cursor;

	collapse_vals: LOOP
		FETCH collapse_cursor INTO v_val;
		IF v_finished = 1 THEN
			LEAVE collapse_vals;
		END IF;
		SET val_list = CONCAT(val_list, v_val, "|");
	END LOOP collapse_vals;

	CLOSE collapse_cursor;

RETURN val_list;
END
 ;;
delimiter ;

-- ----------------------------
--  Function structure for `fn_collapse_tr_env_values_no_serv_names`
-- ----------------------------
DROP FUNCTION IF EXISTS `fn_collapse_tr_env_values_no_serv_names`;
delimiter ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `fn_collapse_tr_env_values_no_serv_names`(`tr_id` int(11)) RETURNS varchar(4000) CHARSET latin1
BEGIN

	DECLARE v_finished INTEGER DEFAULT 0;
	DECLARE v_val varchar(255) DEFAULT "";
	DECLARE val_list varchar(4000) DEFAULT "";

	DECLARE collapse_cursor CURSOR FOR
		select property_value from test_run_environment where test_run_id = tr_id and environment_property not like "%server_name%"  order by environment_property;


	DECLARE CONTINUE HANDLER
	FOR NOT FOUND SET v_finished =1;

	OPEN collapse_cursor;

	collapse_vals: LOOP
		FETCH collapse_cursor INTO v_val;
		IF v_finished = 1 THEN
			LEAVE collapse_vals;
		END IF;
		SET val_list = CONCAT(val_list, v_val, "|");
	END LOOP collapse_vals;

	CLOSE collapse_cursor;

RETURN val_list;
END
 ;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
