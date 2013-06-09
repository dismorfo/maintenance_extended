<?php

/**
 * @file
 *  
 * Maintenance extended
 * A command-line Drupal script for managing your Drupal site maintenance mode
 *
 * Usage:
 * drush maintenance-status
 * drush maintenance-mode-on
 * drush maintenance-mode-off 
 */

/**
 * Implements hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * @see drush_parse_command()
 *   for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function maintenance_extended_drush_command() {

  $items = array();

  $items['maintenance-mode-on'] = array(
    'callback' => 'maintenance_mode_on_callback',
    'description' => dt('Put site into maintenance mode'),
    'arguments' => array(
      'message' => dt('Optional. Set message to show visitors when the site is in maintenance mode.'),
    ),
  );
  
  $items['maintenance-mode-off'] = array(
    'callback' => 'maintenance_mode_off_callback',
    'description' => dt('Go online if operating in maintenance mode'),
  );  
  
  $items['maintenance-status'] = array(
    'callback' => 'maintenance_status_callback',
    'description' => dt('Site status'),
  );
  
  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function maintenance_extended_drush_help($section) {

  switch ($section) {

    case 'drush:maintenance-mode-on':
      return dt("Nothing here");
      break;

    case 'drush:maintenance-mode-off':
      return dt("Nothing here");
      break;  

    case 'maintenance-status':
      return dt("Nothing here");
      break;
  }

}

function maintenance_mode_on_callback() {
  $maintenance_mode = variable_get('maintenance_mode', 0);
  if ($maintenance_mode < 1) {
    return drush_print(  
      (maintenance_extended_go_offline()) ? dt('Successfully enable maintenance mode.') :dt('Error. Unable to enable maintenance mode.')
   ); 
  }
  else {
    return drush_print(
      dt('Nothing to do, site operating in maintenance mode')
    );  
  }  
}

function maintenance_mode_off_callback() {
  $maintenance_mode = variable_get('maintenance_mode', 0);
  if ($maintenance_mode > 0) {
    return drush_print(
      (maintenance_extended_go_online()) ? dt('Site successfully brought back online.') : dt('Error. Unable to bring site back online.')
    );
  }
  else {
    return drush_print(
      dt('Nothing to do, site is already online')
    );  
  }
}

function maintenance_status_callback() {
  return drush_print(
    (variable_get('maintenance_mode', 0)) ? dt('Site operating in maintenance mode') : dt('Site online')
  );  
}