<?php
/**
 * @file
 */

/**
 * class
   $UserInfo = new UserInfo($uid);
   $UserInfo->lastLoginTime();
 *
 */
class UserInfo {
  private $uid;
  private $user = NULL;

  /**
   * @parameter is uid
   */
  function __construct($param){
    $this->uid = $param;

    if (is_numeric($param)) {
      $user = user_load($param);
      if ($user) {
        $this->user = $user;
      }
    }
    else if (is_object($param)) {
      if (isset($param->uid)) {
        $this->uid = $param->uid;
        $this->user = $param;
      }
    }
  }
  /** - - - - - all Methods - - - - - - - - - -  - - - - -   */
  /**
   * all Methods
   */
  protected function allMethods() {
    $methods = NULL;

    /**
     * similar with  $methods = get_class_methods($this);
     */
    $reflect = new ReflectionClass(get_class($this));
    $methods = $reflect->getMethods(ReflectionProperty::IS_PUBLIC);

    return $methods;
  }

  /**
   * all Methods with filter condition
   */
  protected function allMethodsArray() {
    $output = NULL;

    $methods = $this->allMethods();
    if (is_array($methods)) {
      foreach ($methods as $method) {
        if ($method->name != '__construct') {
          if ($method->name != 'allMethodsValue') {
            $output[] = $method->name;
          }
        }
      }
    }
    return $output;
  }

  /**
   * all Methods value
   * @return, array
     array{
       method1 => value1,
       method2 => value2,
     };
   */
  public function allMethodsValue() {
    $output = array();

    $methods = $this->allMethodsArray();
    if (is_array($methods)) {
      $row = '';
      foreach ($methods as $key => $method) {
        $row[$method] = $this->$method();
      }
      $output = $row;
    }
    return $output;
  }

  /**
   * all Methods value
   * @return, array
     array{
       method1 => value1,
       method2 => value2,
     };
   */
  public function basicMethodsValue() {
    $output = array();

    $output['userUid'] = $this->userUid();
    $output['userName'] = $this->userName();
    $output['userEmail'] = $this->userEmail();
    $output['firstName'] = $this->firstName();
    $output['lastName'] = $this->lastName();
    $output['provinceTid'] = $this->provinceTid();
    $output['cityTid'] = $this->cityTid();
    $output['programUnitTids'] = $this->programUnitTids();
    $output['therapeAreaTids'] = $this->therapeAreaTids();


    return $output;
  }

  /** - - - - - Basic Object - - - - - - - - - - - - - - - - - - - - - - - - */

  /** - - - - - user object - - - - - - - - - -  - - - - -   */
  /**
   * @return integer, Uid
   */
  public function randNum($min = 1, $max = 100) {
    $output = rand($min, $max);

    return $output;
  }

  /** - - - - - user object - - - - - - - - - -  - - - - -   */
  /**
   * @return integer, Uid
   */
  public function userUid() {
    $output = NULL;
    if (isset($this->user->uid)) {
      $output = $this->user->uid;
    }
    return $output;
  }
  /**
   * @return String, Name
   */
  public function userName() {
    $output = NULL;
    if (isset($this->user->name)) {
      $output = $this->user->name;
    }
    return $output;
  }
  /**
   * @return String, email
   */
  public function userEmail() {
    $output = NULL;
    if (isset($this->user->mail)) {
      $output = $this->user->mail;
    }
    return $output;
  }
  /**
   * @return Array, integer, Roles RID
   */
  public function userRolesRid() {
    $output = NULL;

    if (isset($this->user->roles)) {
      $output = array_keys($this->user->roles);
    }
    return $output;
  }
  /**
   * @return Array, String, Roles Rid => Role Name
   */
  public function userRolesName() {
    $output = NULL;

    if (isset($this->user->roles)) {
      $output = $this->user->roles;
    }
    return $output;
  }

  /**
   * @return Boolean,
   */
  public function lastLoginTime() {
    $output = NULL;

    if (isset($this->user->login)) {
      if ($this->user->login > 0) {
        $output = TRUE;
      }
    }
    return $output;
  }
  /**
   * @return interger, unix timestamp
   */
  public function lastLoginTimeStamp() {
    $output = NULL;

    if (isset($this->user->login)) {
      $output = $this->user->login;
    }
    return $output;
  }
  /**
   * @return string, date unix stamp
   */
  public function lastLoginTimeFormat($format = NULL) {
    if (!$format) {
      $format = "Y-m-d";
    }

    $output = NULL;
    $stamp = $this->lastLoginTimeStamp();
    if ($stamp) {
      $output = format_date($stamp, 'custom', $format);
    }
    return $output;
  }
  /**
   * @return string, date unix stamp
   */
  public function lastLoginTimeInterval($format = NULL) {
    if (!$format) {
      $format = "Y-m-d";
    }

    $output = NULL;
    $stamp = $this->lastLoginTimeStamp();
    if ($stamp) {
      $diff = time() - $stamp;
      $output = format_interval($diff, 1);
    }
    return $output;
  }

  /**
   * @return string, like (America/Toronto, America/Vancouver)
   */
  public function timezone() {
    $output = NULL;

    if (isset($this->user->timezone)) {
      $output = $this->user->timezone;
    }
    return $output;
  }

  /** - - - - - user field - - - - - - - - - - - - - - - - - - - - - -   */

  /**
   * @return String, First Name
   */
  public function firstName() {
    $output = NULL;

    if (isset($this->user->field_user_first_name['und'][0]['safe_value'])) {
      $output = $this->user->field_user_first_name['und'][0]['safe_value'];
    }
    return $output;
  }
  /**
   * @return String, Last Name
   */
  public function lastName() {
    $output = NULL;

    if (isset($this->user->field_user_last_name['und'][0]['safe_value'])) {
      $output = $this->user->field_user_last_name['und'][0]['safe_value'];
    }
    return $output;
  }
  /**
   * @return String,
   */
  public function fullname() {
    $output = NULL;

    $fullname = NULL;
    if ($this->firstName()) {
      $fullname[] = $this->firstName();
    }
    if ($this->lastName()) {
      $fullname[] = $this->lastName();
    }

    if (is_array($fullname)) {
      $output = implode(" ", $fullname);
    }
    else {
      if ($this->user) {
        $output = $this->user->name;
      }
    }

    return $output;
  }

  /**
   * @return String, Province Tid
   */
  public function cityTid() {
    $output = NULL;

    if (isset($this->user->field_user_city['und'][0]['target_id'])) {
      $output = $this->user->field_user_city['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function cityName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->cityTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return String, Province Tid
   */
  public function provinceTid() {
    $output = NULL;

    if (isset($this->user->field_user_province['und'][0]['target_id'])) {
      $output = $this->user->field_user_province['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function provinceName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->provinceTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return String, location is combine city and province
   */
  public function location() {
    $output = NULL;

    $location = array();
    if ($this->cityName()) {
      $location[] = $this->cityName();
    }
    if ($this->provinceName()) {
      $location[] = $this->provinceName();
    }

    if (is_array($location)) {
      $output = implode(" ", $location);
    }

    return $output;
  }

  /**
   * @return String, timezoneValue for sepecify user, like (America/Toronto, America/Vancouver)
   */
  public function userTimezoneValue() {
    $output = NULL;

    if ($this->timezone()) {
      $output = $this->timezone();
    }
    else {
      $output = date_default_timezone_get();
    }
    return $output;
  }
  /**
   * @return integer, timezone offset Value for sepecify user,
   * return (-14400 for America/Toronto)
            (-25200 for America/Vancouver)
   */
  public function userTimezoneOffsetValue() {
    $output = NULL;

    if ($this->userTimezoneValue()) {
      $timezone = $this->userTimezoneValue();

      $this_tz = new DateTimeZone($timezone);
      $now = new DateTime("now", $this_tz);
      $output = $this_tz->getOffset($now);
    }

    return $output;
  }

  /**
   * @return array, integer
   */
  public function programUnitTids() {
    $output = NULL;

    if (isset($this->user->field_user_program_unit['und'][0]['target_id'])) {
      foreach ($this->user->field_user_program_unit['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
  /**
   * @return array, String, Term Name
   */
  public function programUnitName() {
    $output = NULL;

    if (is_array($this->programUnitTids())) {
      foreach ($this->programUnitTids() as $key => $value) {
        $TermInfo = new TermInfo($value);
        $output[] = $TermInfo->termName();
      }
    }
    return $output;
  }

  /**
   * @return array, integer
   */
  public function therapeAreaTids() {
    $output = NULL;

    if (isset($this->user->field_user_therapeutic_area['und'][0]['target_id'])) {
      foreach ($this->user->field_user_therapeutic_area['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
  /**
   * @return array, String, Term Name
   */
  public function therapeAreaName() {
    $output = NULL;

    if (is_array($this->therapeAreaTids())) {
      foreach ($this->therapeAreaTids() as $key => $value) {
        $TermInfo = new TermInfo($value);
        $output[] = $TermInfo->termName();
      }
    }
    return $output;
  }


  /** - - - - - user Avatar - - - - - - - - - -  - - - - -   */
  /**
   * @return User avatar
   */
  public function userAvatarImage() {
    $user_avatar = NULL;

    if( isset($this->user->picture) ){
      $file = file_load($this->user->picture->fid);

      if ($file) {
        $image = array(
          'path' => $file->uri,
          'alt' => 'avatar',
          'attributes' => array('class' => 'img-circle'),
          'width' => 48,
          'height' => 48,
        );
        $user_avatar = theme('image', $image);
      }
    }
    return $user_avatar;
  }

}
