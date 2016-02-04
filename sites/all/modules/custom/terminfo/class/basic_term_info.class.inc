<?php
/**
 * @file
   $TermInfo = new TermInfo($tid);
   $TermInfo->provinceTidByCity();
 *
 */

/**
 * class
   $TermInfo = new TermInfo($tid);
   $TermInfo->termName();
 */
class TermInfo {
  protected $tid;
  protected $term = NULL;

  /**
   * @parameter is tid
   */
  public function __construct($param){
    if (is_numeric($param)) {
      $term = taxonomy_term_load($param);
      if ($term) {
        $this->term = $term;
        $this->tid = $param;
      }
    }
    else if (is_object($param)) {
      if (isset($param->tid)) {
        $this->term = taxonomy_term_load($param->tid);
        $this->tid = $param->tid;
      }
    }
  }

  /** - - - - - Basic Object - - - - - - - - - -  - - - - -   */
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

    $output['termTid'] = $this->termTid();
    $output['termName'] = $this->termName();

    return $output;
  }

  /** - - - - - Basic Object - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * @return Term Name
   */
  public function termTid() {
    $output = NULL;
    if ($this->term) {
      $output = $this->term->tid;
    }
    return $output;
  }
  /**
   * @return Term Name
   */
  public function termName() {
    $output = NULL;
    if ($this->term) {
      $output = $this->term->name;
    }
    return $output;
  }
  /**
   * @return Term Vid
   */
  public function termVid() {
    $output = NULL;
    if ($this->term) {
      $output = $this->term->vid;
    }
    return $output;
  }
  /**
   * @return Term Vid
   */
  public function termVidName() {
    $output = NULL;
    $vocabulary = taxonomy_vocabulary_load($this->termVid());
    if ($vocabulary) {
      $output = $vocabulary->name;
    }
    return $output;
  }
  /**
   * @return Term Description
   */
  public function termDescription() {
    $output = NULL;
    if ($this->term) {
      $output = $this->term->description;
    }
    return $output;
  }

  /**
   * @return Term Description
   */
  public function termEditLink() {
    $output = NULL;
    if ($this->term) {
      $output = base_path() . 'manage/term/edit/' . $this->termVid() . '/' . $this->termTid();
    }
    return $output;
  }

}

/**
 * class
   $TermBrandInfo = new TermBrandInfo($tid);
   $TermBrandInfo->evaluationFormTid();
 */
class TermBrandInfo extends TermInfo {

}

