<?php
/**
 *
  drupal_set_time_limit(0);
  require_once(DRUPAL_ROOT . '/sites/all/modules/custom/developinfo/caiji_game.php');
  run_caiji_game();
 */
run_caiji_game();
function run_caiji_game() {
  $url = 'http://www.okooo.com/soccer/match/720555/odds/';

  dpm(caiji_by_file_get_contents($url));
  dpm(caiji_by_curl($url));
}

function caiji_by_file_get_contents($url) {
  $data = file_get_contents($url);
  return $data;
}

/* gets the data from a URL */
function caiji_by_curl($url) {
  $ch = curl_init();
  $timeout = 5;
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);

  $data = curl_exec($ch);
  curl_close($ch);

  return $data;
}
