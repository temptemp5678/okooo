<?php
/**
 * @file
 */

/**
 * class
   $SettingInfo = new SettingInfo();
   $SettingInfo->siteLogoImage();
 */
class SettingInfo {
  /**
   * @return site logo
   */
  public function siteLogoImage() {
    $logo_image = NULL;
    if (theme_get_setting('logo')) {
      $image = array(
        'path' => theme_get_setting('logo'),
        'alt' => 'Site Logo',
        'attributes' => array('class' => 'site-logo'),
      );
      $logo_image = theme('image', $image);
    }

    return $logo_image;
  }

  /**
   * @return site logo
   */
  public function siteLogoHTML() {
    $logo_image = $this->siteLogoImage();

    $output = NULL;
    if ($logo_image) {
      $output .= '<div class="color-fff">';
        $output .= $logo_image;
      $output .= '</div>';
    }
    return $output;
  }

}

/**
 * class
   $BasicClass = new BasicClass();
   BasicClass::camelCase();
 */
class BasicClass {

  /**
   * avoid Warning: array_sum() / count(() expects parameter 1 to be array, null given
   */
  public static function arrayAverage($items = array()) {
    $output = 0;
    if (is_array($items)) {
      if (count($items) > 0) {
        $output = array_sum($items) / count($items);
      }
    }

    return $output;
  }

  /**
   * avoid Warning: array_count_values() expects parameter 1 to be array, null given
   */
  public static function arrayCountValues($items = array()) {
    $output = 0;
    if (is_array($items)) {
      if (count($items) > 0) {
        $output = array_count_values($items);
      }
    }

    return $output;
  }

  /**
   * avoid Warning: array_count_values() expects parameter 1 to be array, null given
   * avoid Warning: Notice: Undefined offset: 1, because some array key is missing
   */
  public static function arrayCountValuesBySpecifyArray($items = array(), $specify_keys = array()) {
    $output = array();

    foreach ($specify_keys as $row) {
      // Firstly set default value cause array is empty, it will warning Undefined offset:
      $output[$row] = 0;
    }

    if (is_array($items) && is_array($specify_keys) ) {
      foreach ($specify_keys as $row) {
        $output[$row] = count(array_keys($items, $row));
      }
    }

    return $output;
  }

  /**
   * avoid Warning: array_sum() expects parameter 1 to be array, null given
   */
  public static function arraySum($items = array()) {
    $output = NULL;
    if (is_array($items)) {
      $output = array_sum($items);
    }

    return $output;
  }

  /**
   * convert a string to a camel case string
   */
  public static function camelCase($str, $noStrip = array()) {
    // non-alpha and non-numeric characters become spaces
    $str = preg_replace('/[^a-z0-9' . implode("", $noStrip) . ']+/i', ' ', $str);
    $str = trim($str);
    // uppercase the first character of each word
    $str = ucwords($str);
    $str = str_replace(" ", "", $str);
    $str = lcfirst($str);

    return $str;
  }

  /**
   * avoid Warning: array_sum() expects parameter 1 to be array, null given
   */
  public static function implode($glue = ' ', $pieces = array()) {
    $output = NULL;
    if (is_array($pieces)) {
      $output = implode($glue, $pieces);
    }

    return $output;
  }

  /**
   * avoid number 2 is zero or null
   */
  public static function percentage($num1 = NULL, $num2 =NULL) {
    $output = t('N/A');

    if ($num2 > 0) {
      $output = intval(($num1 / $num2) * 100);
    }

    return $output;
  }


}

/**
 * class
   $DateTimeClass = new DateTimeClass();
   $DateTimeClass->user_set_date_range();
 */
class DateTimeClass {
  /**
   * Checks if a string is a valid UNIX timestamp.
   *
   * @param  string $timestamp Timestamp to validate.
   *
   * @return Boolean
   */
  public function is_timestamp($timestamp) {
    $check = (is_int($timestamp) OR is_float($timestamp))
             ? $timestamp
             : (string) (int) $timestamp;

    $result = ($check === $timestamp)
              AND ( (int) $timestamp <=  PHP_INT_MAX)
              AND ( (int) $timestamp >= ~PHP_INT_MAX);

    return $result;
  }

  /**
   *
   * a timestamp for first day midnight of current year, (12:00:00 am)
   *
   * @return UNIX timestamp
   */
  public function timeStampYearFirstDay() {
    // $end_date = $end_date + (60 * 60 * 24 - 1);
    $first_day = new DateTime();
    $current_year = $first_day->format('Y');
    $first_day->setDate($current_year, 01, 01);
    $first_day->setTime(0, 0);

    $result = $first_day->getTimestamp();
    return $result;
  }

  /**
   *
   * a timestamp for today night last minutes, (23:59:59 pm)
   *
   * @return UNIX timestamp
   */
  public function timeStampToday() {
    // $end_date = $end_date + (60 * 60 * 24 - 1);
    $today = new DateTime();
    $today->setTime(23, 59, 59);

    $result = $today->getTimestamp();
    return $result;
  }

  /**
   *
   * a timestamp for today night last minutes, (23:59:59 pm)
   *
   * @return UNIX timestamp
   */
  public function dateValue($timestamp = NULL, $format = 'F j, Y') {
    $output = NULL;

    if ($timestamp) {
      if ($this->is_timestamp($timestamp)) {

        $date_object = new DateTime("@$timestamp");
        $output = $date_object->format($format);
      }
    }

    return $output;
  }


  /**
   * @return array, get user start_time and end_time timestamp
   */
  public function user_get_date_range() {
    $output = NULL;

    global $user;

    if (isset($user->data['start_time']) && isset($user->data['end_time'])) {
      $output = array(
        'start_time' => $user->data['start_time'],
        'end_time' => $user->data['end_time'],
      );
    }
    else {
      // set YTD,  'Year To Date - YTD' The period beginning January 1st of the current year up until today's date.
      $DateTimeClass = new DateTimeClass();
      // get label for start date, and end date
      $output = array(
        'start_time' => $this->timeStampYearFirstDay(),
        'end_time' => $this->timeStampToday(),
      );
    }

    return $output;
  }

  /**
   * @return string, get user start_time and end_time timestamp
   */
  public function user_get_date_range_path_suffix() {
    $output = NULL;

    $date_range = $this->user_get_date_range();

    if (isset($date_range['start_time'])) {
      $output = $date_range['start_time'] . '/' . $date_range['end_time'];
    }

    return $output;
  }

  /**
   * @return string, get user start_time and end_time timestamp
   */
  public function user_set_date_range($start_time = NULL, $end_time = NULL) {
    $output = NULL;

    if ($start_time && $end_time) {
      global $user;
      $DateTimeClass = new DateTimeClass();

      if ($DateTimeClass->is_timestamp($start_time) && $DateTimeClass->is_timestamp($end_time)) {
        $edit = array(
          'data' => array(
            'start_time' => $start_time,
            'end_time' => $end_time,
          ),
        );

        user_save($user, $edit);
        // watchdog('jsonservice', 'user action set_date_range()');
      }
    }

    return $output;
  }

}
