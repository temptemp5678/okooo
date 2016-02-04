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

/**
 * class
   $TermCityInfo = new TermCityInfo($tid);
   $TermCityInfo->labelTitleArray();
 */
class TermCityInfo extends TermInfo {
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
    $output['provinceTid'] = $this->provinceTid();
    $output['provinceName'] = $this->provinceName();

    return $output;
  }

  /** - - - - - Basic - - - - - - - - - - - - - - - - - - - - - - - - */
  /**
   * @return String, latitude
   */
  public function latitude() {
    $output = NULL;

    if (isset($this->term->field_city_latlon_lat['und'][0]['value'])) {
      $output = $this->term->field_city_latlon_lat['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return String, longitude
   */
  public function longitude () {
    $output = NULL;

    if (isset($this->term->field_city_latlon_lon['und'][0]['value'])) {
      $output = $this->term->field_city_latlon_lon['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return String, Province Tid
   */
  public function provinceTid() {
    $output = NULL;

    if (isset($this->term->field_city_province['und'][0]['target_id'])) {
      $output = $this->term->field_city_province['und'][0]['target_id'];
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
}

/**
 * class
   $TermEvaluationFormInfo = new TermEvaluationFormInfo($tid);
   $TermEvaluationFormInfo->questionNumber();
 */
class TermEvaluationFormInfo extends TermInfo {
  /**
   * @return Array
   */
  public function questionSetArray() {
    $output = NULL;
    if (isset($this->term->field_quesset_question['und'][0]['quesset_question_tid'])) {
      $output = $this->term->field_quesset_question['und'];
    }

    return $output;
  }

  /**
   * @return integer, for count number
   */
  public function numberOfQuestion() {
    $output = NULL;

    $output = count($this->questionSetArray());

    return $output;
  }

  /**
   * @return
   */
  public function questionSetList() {
    $output = NULL;

    if (is_array($this->questionSetArray())) {
      foreach ($this->questionSetArray() as $key => $value) {

        if (isset($value['quesset_question_tid'])) {
          $TermQuestionLibInfo = new TermQuestionLibInfo($value['quesset_question_tid']);

          $TermQuestionFieldInfo = new TermQuestionFieldInfo($TermQuestionLibInfo->fieldTid());

          if (is_array($TermQuestionFieldInfo->multipleFieldsTidArray())) {

            // only first fieldTid has number and title
            $title_boolean = TRUE;
            foreach ($TermQuestionFieldInfo->multipleFieldsTidArray() as $fieldTid) {
              $TermFormFieldInfo = new TermFormFieldInfo($fieldTid);


              $question_label = '';
              if (is_array($TermQuestionLibInfo->labelTitleValueArray())) {
                $question_label = array_slice($TermQuestionLibInfo->labelTitleValueArray(), 0, $TermQuestionLibInfo->lengthValue());
              }

              $row = '';
              $row = array(
                'questionTid' => $value['quesset_question_tid'],    // question library
                'questionFieldName' => $TermFormFieldInfo->termName(),
                'questionFieldTid' => $fieldTid,
                'questionNumber' => $title_boolean ? $value['quesset_number'] : '',
                'questionTitle'  => $title_boolean ? $TermQuestionLibInfo->termName() : '',
                'questionLabel' => $question_label,
                'questionValue' => '',                             // when create evaluation, value is null
              );

              $title_boolean = FALSE;
              $output[] = $row;
            }
          }

        }

      }
    }
    return $output;
  }
}

/**
 * class
   $TermFormFieldInfo = new TermFormFieldInfo($tid);
   $TermFormFieldInfo->termName();
 */
class TermFormFieldInfo extends TermInfo {

}

/**
 * class
   $TermMeetingTypeInfo = new TermMeetingTypeInfo($tid);
   $TermMeetingTypeInfo->termName();
 */
class TermMeetingTypeInfo extends TermInfo {

}

/**
 * class
   $TermMeetingReceivedInfo = new TermMeetingReceivedInfo($tid);
   $TermMeetingReceivedInfo->termName();
 */
class TermMeetingReceivedInfo extends TermInfo {

}

/**
 * class Multi-Therapeutic Event
   $TermMultiTherapeInfo = new TermMultiTherapeInfo($tid);
   $TermMultiTherapeInfo->termName();
 */
class TermMultiTherapeInfo extends TermInfo {

}
/**
 * class Multi-Therapeutic Event
   $TermQuestionLibraryInfo = new TermQuestionLibraryInfo($tid);
   $TermQuestionLibraryInfo->termName();
 */
class TermQuestionLibraryInfo extends TermInfo {
  /**
   * @return integer, Tid
   */
  public function questionFieldlTid() {
    $output = NULL;

    if (isset($this->term->field_queslibr_ques_field['und'][0]['target_id'])) {
      $output = $this->term->field_queslibr_ques_field['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function questionFieldName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->questionFieldlTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return integer, Tid
   */
  public function questionLabelTid() {
    $output = NULL;

    if (isset($this->term->field_queslibr_label['und'][0]['target_id'])) {
      $output = $this->term->field_queslibr_label['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function questionLabelName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->questionLabelTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return integer, Tid
   */
  public function questionScale() {
    $output = NULL;

    if (isset($this->term->field_queslibr_length['und'][0]['value'])) {
      $output = $this->term->field_queslibr_length['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return integer, Tid
   */
  public function questionLegend() {
    $output = NULL;

    if (isset($this->term->field_queslibr_legend['und'][0]['value'])) {
      foreach ($this->term->field_queslibr_legend['und'] as $value) {
        $output[] = $value['value'];
      }
    }
    return $output;
  }
}

/**
 * class
   $TermProgramInfo = new TermProgramInfo($tid);
   $TermProgramInfo->programUnitName();
 */
class TermProgramInfo extends TermInfo {
  /**
   * @return integer, Tid
   */
  public function evaluationFormTid() {
    $output = NULL;

    if (isset($this->term->field_program_evaluation_form['und'][0]['target_id'])) {
      $output = $this->term->field_program_evaluation_form['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function evaluationFormName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->evaluationFormTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }
  /**
   * @return array,
   */
  public function questionSetArray() {
    $output = NULL;
    if ($this->evaluationFormTid()) {
      $TermEvaluationFormInfo = new TermEvaluationFormInfo($this->evaluationFormTid());
      $output = $TermEvaluationFormInfo->questionSetArray();
    }
    return $output;
  }

  /**
   * @return integer, Tid
   */
  public function programClassTids() {
    $output = NULL;

    if (isset($this->term->field_program_programclass['und'][0]['target_id'])) {
      foreach ($this->term->field_program_programclass['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
  /**
   * @return string
   */
  public function programClassNames() {
    $output = NULL;

    if ($this->programClassTids()) {
      if (is_array($this->programClassTids())) {
        foreach ($this->programClassTids() as $key => $value) {
          $TermProgramClassInfo = new TermProgramClassInfo($value);
          $output[] = $TermProgramClassInfo->termName();
        }
      }
    }
    return $output;
  }


  /**
   * @return integer, Tid
   */
  public function programTypeTids() {
    $output = NULL;

    if (isset($this->term->field_program_programtype['und'][0]['target_id'])) {
      foreach ($this->term->field_program_programtype['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
  /**
   * @return string
   */
  public function programTypeNames() {
    $output = NULL;

    if ($this->programTypeTids()) {
      if (is_array($this->programTypeTids())) {
        foreach ($this->programTypeTids() as $key => $value) {
          $TermProgramTypeInfo = new TermProgramTypeInfo($value);
          $output[] = $TermProgramTypeInfo->termName();
        }
      }
    }
    return $output;
  }

  /**
   * @return integer, Tid
   */
  public function programUnitTid() {
    $output = NULL;

    if (isset($this->term->field_program_programunit['und'][0]['target_id'])) {
      $output = $this->term->field_program_programunit['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return string
   */
  public function programUnitName() {
    $output = NULL;

    if ($this->programUnitTid()) {
      $TermProgramUnitInfo = new TermProgramUnitInfo($this->programUnitTid());
      $output = $TermProgramUnitInfo->termName();;
    }

    return $output;
  }

  /**
   * @return integer, Tid
   */
  public function therapAreaTids() {
    $output = NULL;

    if (isset($this->term->field_program_theraparea['und'][0]['target_id'])) {
      foreach ($this->term->field_program_theraparea['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
  /**
   * @return string
   */
  public function therapAreaNames() {
    $output = NULL;

    if ($this->therapAreaTids()) {
      if (is_array($this->therapAreaTids())) {
        foreach ($this->therapAreaTids() as $key => $value) {
          $TermTherapeuticAreaInfo = new TermTherapeuticAreaInfo($value);
          $output[] = $TermTherapeuticAreaInfo->termName();
        }
      }
    }
    return $output;
  }
}

/**
 * class
   $TermProgramClassInfo = new TermProgramClassInfo($tid);
   $TermProgramClassInfo->termName();
 */
class TermProgramClassInfo extends TermInfo {
}

/**
 * class
   $TermProgramNationInfo = new TermProgramNationInfo($tid);
   $TermProgramNationInfo->termName();
 */
class TermProgramNationInfo extends TermInfo {
}

/**
 * class
   $TermProgramTypeInfo = new TermProgramTypeInfo($tid);
   $TermProgramTypeInfo->termName();
 */
class TermProgramTypeInfo extends TermInfo {
}

/**
 * class
   $TermProgramUnitInfo = new TermProgramUnitInfo($tid);
   $TermProgramUnitInfo->termName();
 */
class TermProgramUnitInfo extends TermInfo {
  /**
   * @return Array,
   */
  public function brandTids() {
    $output = NULL;
    if (isset($this->term->field_unit_brands['und'][0]['target_id'])) {
      foreach ($this->term->field_unit_brands['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
  /**
   * @return Array,
   */
  public function brandTerms() {
    $output = NULL;

    if (is_array($this->brandTids())) {
      foreach ($this->brandTids() as $key => $tid) {
        $TermBrandInfo = new TermBrandInfo($tid);
        $output[] = $TermBrandInfo->allMethodsValue();
      }
    }
    return $output;
  }

  /**
   * @return Array,
   */
  public function nationTid() {
    $output = NULL;
    if (isset($this->term->field_unit_nation['und'][0]['target_id'])) {
      $output = $this->term->field_unit_nation['und'][0]['target_id'];
    }
    return $output;
  }

  /**
   * @return Array,
   */
  public function therapeuticAreaTids() {
    $output = NULL;
    if (isset($this->term->field_unit_therap_area['und'][0]['target_id'])) {
      foreach ($this->term->field_unit_therap_area['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
  /**
   * @return Array,
   */
  public function therapeuticAreaTerms() {
    $output = NULL;

    if (is_array($this->therapeuticAreaTids())) {
      foreach ($this->therapeuticAreaTids() as $key => $tid) {
        $TermTherapeuticAreaInfo = new TermTherapeuticAreaInfo($tid);
        $output[] = $TermTherapeuticAreaInfo->allMethodsValue();
      }
    }
    return $output;
  }
}

/**
 * class
   $TermProgramClassInfo = new TermProgramClassInfo($tid);
   $TermProgramClassInfo->termName();
 */
class TermProvinceInfo extends TermInfo {
  /**
   * @return String, Term Property
   */
  public function provinceNameAbbr() {
    $output = NULL;
    if (isset($this->term->field_field_province_abbr_name['und'][0]['value'])) {
      $output = $this->term->field_field_province_abbr_name['und'][0]['value'];
    }

    return $output;
  }
}

/**
 * class
   $TermQuestionFieldInfo = new TermQuestionFieldInfo($tid);
   $TermQuestionFieldInfo->multipleFieldsTidArray();
 */
class TermQuestionFieldInfo extends TermInfo {
  /**
   * @return Array,
   */
  public function multipleFieldsTidArray() {
    $output = NULL;
    if (isset($this->term->field_quesfield_multiple_fields['und'][0]['target_id'])) {
      foreach ($this->term->field_quesfield_multiple_fields['und'] as $key => $value) {
        $output[] = $value['target_id'];
      }
    }
    return $output;
  }
}

/**
 * class
   $TermQuestionLabelInfo = new TermQuestionLabelInfo($tid);
   $TermQuestionLabelInfo->labelTitleArray();
 */
class TermQuestionLabelInfo extends TermInfo {
  /**
   * @return Array,
   */
  public function labelTitleArray() {
    $output = NULL;

    if (isset($this->term->field_queslabel_title['und'][0]['safe_value'])) {
      $output = $this->term->field_queslabel_title['und'];
    }
    return $output;
  }

}

/**
 * class
   $TermQuestionLibInfo = new TermQuestionLibInfo($tid);
   $TermQuestionLibInfo->chartTypeTid();
 */
class TermQuestionLibInfo extends TermInfo {
  /**
   * @return integer,
   */
  public function fieldTid() {
    $output = NULL;

    if (isset($this->term->field_queslibr_ques_field['und'][0]['target_id'])) {
      $output = $this->term->field_queslibr_ques_field['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function fieldName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->fieldTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return integer,
   */
  public function labelTid() {
    $output = NULL;

    if (isset($this->term->field_queslibr_label['und'][0]['target_id'])) {
      $output = $this->term->field_queslibr_label['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return Array,
   */
  public function labelTitleArray() {
    $output = NULL;

    if ($this->labelTid()) {
      $TermQuestionLabelInfo = new TermQuestionLabelInfo($this->labelTid());
      $output = $TermQuestionLabelInfo->labelTitleArray();
    }
    return $output;
  }
  /**
   * @return Array,
   */
  public function labelTitleValueArray() {
    $output = NULL;

    if ($this->labelTitleArray()) {
      foreach ($this->labelTitleArray() as $key => $value) {
        $output[$value['safe_value']] = $value['safe_value'];
      }
    }
    return $output;
  }

  /**
   * @return integer,
   */
  public function lengthValue() {
    $output = NULL;

    if (isset($this->term->field_queslibr_length['und'][0]['value'])) {
      $output = $this->term->field_queslibr_length['und'][0]['value'];
    }
    return $output;
  }
}

/**
 * class
   $TermTherapeuticAreaInfo = new TermTherapeuticAreaInfo($tid);
   $TermTherapeuticAreaInfo->chartTypeTid();
 */
class TermTherapeuticAreaInfo extends TermInfo {

}
