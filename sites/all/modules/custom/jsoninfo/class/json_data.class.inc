<?php
/**
 * class
   $JsonDataUnit = new JsonDataUnit();
   $JsonDataUnit->sourceArrayData();
 *
 */
class JsonDataUnit {

  /** - - - - - Node Json- - - - - - - - - - - - - - - */
  /**
   * @return Array data
   */
  public function nodeEventList($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $NodeQuery = new NodeQuery();

    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    $nodes = node_load_multiple($meetings);

    if (is_array($nodes)) {
      foreach ($nodes as $key => $node) {
        $MeetingInfo = new MeetingInfo($node->nid);

        $output[] = array(
          'eventNid' => $node->nid,
          'eventName' => $MeetingInfo->programName(),
          'eventProgramName' => $MeetingInfo->programName(),
          'eventDescrption' => '',
          'eventDate' => $MeetingInfo->dateValue(),
          'eventCity' => $MeetingInfo->cityName(),
          'eventProvince' => $MeetingInfo->provinceName(),
          'eventSpeaker' => $MeetingInfo->speakerName(),
          'eventRep' => $MeetingInfo->repName(),
          'editText' => 'EDIT',
          'evaluationFormName' => 'CFPC Evaluation Form',
          'evaluationFormNumber' => 3,
          'linkCreateEvent' => '\/lillydash\/manage\/meeting\/create\/60',
          'linkEdit' => '\/lillydash\/manage\/term\/edit\/2\/60?destination=manage\/program\/list'
        );
      }
    }

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function nodeMeeting() {
    $output = $this->termStandardJson(19, 'TermBrandInfo');
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function nodeMeetingMap($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $NodeQuery = new NodeQuery();

    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    $meeting_nodes = node_load_multiple($meetings);

    $output = array();
    foreach ($meeting_nodes as $key => $node) {
      $MeetingInfo = new MeetingInfo($node->nid);
      $TermProgramInfo = new TermProgramInfo($MeetingInfo->programTid());

      if ($MeetingInfo->latitude() && $MeetingInfo->longitude()) {
        $output[$node->nid] = array(
          "lat" => $MeetingInfo->latitude(),
          "lng" => $MeetingInfo->longitude(),
          "pageUrl" => '#1',
          "unitName" => $TermProgramInfo->programUnitName(),
          "programName" => $MeetingInfo->programName(),
          "meetingDate" => $MeetingInfo->dateValue(),
          "meetingLocation" => $MeetingInfo->provinceName(),
          "speakerName" => $MeetingInfo->speakerName(),
          "speakerNameUrl" => '#',
          "repName" => $MeetingInfo->repName(),
          "evaluationCount" => $MeetingInfo->programTid(),
          "venuName"  => $MeetingInfo->cityName() . ', ' . $MeetingInfo->provinceName(),
          "venuType"  => $MeetingInfo->meetingTypeName(),
          "attendiesCount"  => $MeetingInfo->signatures(),
          "619" => l('Event Link', '#'),
        );
      }
    }
    return $output;
  }

  /** - - - - - Term Standard Json- - - - - - - - - - - - - - - - - - - - - - */
  /**
   * @return Term Array data
   */
  public function pushDefaultValue($import_array = NULL, $default_value = array()) {
    $output = NULL;
    if (is_array($import_array)) {
      $output[] = $default_value;
      $output += $import_array;
    }

    return $output;
  }

  /** - - - - - Term Standard Json- - - - - - - - - - - - - - - - - - - - - - */
  /**
   * @return Term Array data by specify VID
   */
  public function termStandardJson($vid = NULL, $class_name = NULL, $basic = NULL) {
    if ($class_name) {
      $all_term_array = taxonomy_get_tree($vid);

      if (is_array($all_term_array)) {
        foreach ($all_term_array as $term_key => $term_row) {
          // $TermProgramInfo = new TermProgramInfo($term_row->tid);
          $TermClassInfo = new $class_name($term_row->tid);

          if ($basic) {
            $output[] = $TermClassInfo->basicMethodsValue();
          }
          else {
            $output[] = $TermClassInfo->allMethodsValue();
          }
        }
      }
    }

    return $output;
  }

  /** - - - - - Term - - - - - - - - - - - - - - - */
  /**
   * @return Term Array data
   */
  public function termBrand($basic = NULL) {
    $output = $this->termStandardJson(19, 'TermBrandInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termBusinessUnit($basic = NULL) {
    $output = $this->termStandardJson(11, 'TermProgramUnitInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termBusinessUnitOld() {
    $output = NULL;

    $all_term_array = taxonomy_get_tree(11);

    if (is_array($all_term_array)) {
      foreach ($all_term_array as $term_key => $term_row) {
        $TermProgramUnitInfo = new TermProgramUnitInfo($term_row->tid);

        $extra_array = array(
          'linkEdit' => base_path() . 'manage/program-unit/edit/' . $term_row->tid . '?destination=manage/program/list',
        );

        $output[] = ($extra_array + ($TermProgramUnitInfo->allMethodsValue()));
      }
    }

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termBusinessUnitTree() {
    $output = NULL;

    $unit_tids = taxonomy_get_tree(11);

    if (is_array($unit_tids)) {
      foreach ($unit_tids as $unit_tid) {
        $TermProgramUnitInfo = new TermProgramUnitInfo($unit_tid);

        if (is_array($TermProgramUnitInfo->therapeuticAreaTids())) {
          foreach ($TermProgramUnitInfo->therapeuticAreaTids() as $therapeuticAreaTid) {
            $TermTherapeuticAreaInfo = new TermTherapeuticAreaInfo($therapeuticAreaTid);

            if (is_array($TermProgramUnitInfo->brandTids())) {
              foreach ($TermProgramUnitInfo->brandTids() as $brandTid) {
                $TermBrandInfo = new TermBrandInfo($brandTid);

                $output[] = array(
                  'businessUnitTermTid' => $TermProgramUnitInfo->termTid(),
                  'businessUnitTermName' => $TermProgramUnitInfo->termName(),
                  'therapeuticAreaTermTid' => $TermTherapeuticAreaInfo->termTid(),
                  'therapeuticAreaTermName' => $TermTherapeuticAreaInfo->termName(),
                  'brandTermTid' => $TermBrandInfo->termTid(),
                  'brandTermName' => $TermBrandInfo->termName(),
                  'programNumber' => rand(1, 10),
                  'eventNumber' => rand(10, 40),
                );
              }
            }
            else {
              $output[] = array(
                'businessUnitTermTid' => $TermProgramUnitInfo->termTid(),
                'businessUnitTermName' => $TermProgramUnitInfo->termName(),
                'therapeuticAreaTermTid' => $TermTherapeuticAreaInfo->termTid(),
                'therapeuticAreaTermName' => $TermTherapeuticAreaInfo->termName(),
                'programNumber' => rand(1, 10),
                'eventNumber' => rand(10, 40),
              );
            }
          }
        }
      }
    }

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termCity($basic = NULL) {
    $output = $this->termStandardJson(18, 'TermCityInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termEvaluationForm($basic = NULL) {
    $output = $this->termStandardJson(6, 'TermEvaluationFormInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termMeetingType($basic = NULL) {
    $output = $this->termStandardJson(16, 'TermMeetingTypeInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termMeetingReceived($basic = NULL) {
    $output = $this->termStandardJson(20, 'TermMeetingReceivedInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data, Multi-Therapeutic Event
   */
  public function termMultiTherape($basic = NULL) {
    $output = $this->termStandardJson(21, 'TermMultiTherapeInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termProgram($basic = NULL) {
    $output = $this->termStandardJson(2, 'TermProgramInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termProgramTree() {
    $output = NULL;

    $program_tids = taxonomy_get_tree(2);

    if (is_array($program_tids)) {
      foreach ($program_tids as $program_tid) {
        $TermProgramInfo = new TermProgramInfo($program_tid);

        if (is_array($TermProgramInfo->programTypeTids())) {
          foreach ($TermProgramInfo->programTypeTids() as $therapeuticAreaTid) {
            $TermProgramTypeInfo = new TermProgramTypeInfo($therapeuticAreaTid);

            if (is_array($TermProgramInfo->programClassTids())) {
              foreach ($TermProgramInfo->programClassTids() as $programClassTid) {
                $TermProgramClassInfo = new TermProgramClassInfo($programClassTid);

                $output[] = array(
                  'programTermTid' => $TermProgramInfo->termTid(),
                  'programTermName' => $TermProgramInfo->termName(),
                  'programTypeTermTid' => $TermProgramTypeInfo->termTid(),
                  'programTypeTermName' => $TermProgramTypeInfo->termName(),
                  'programClassTid' => $TermProgramClassInfo->termTid(),
                  'programClassName' => $TermProgramClassInfo->termName(),
                );
              }
            }
            else {
              $output[] = array(
                'programTermTid' => $TermProgramInfo->termTid(),
                'programTermName' => $TermProgramInfo->termName(),
                'programTypeTermTid' => $TermProgramTypeInfo->termTid(),
                'programTypeTermName' => $TermProgramTypeInfo->termName(),
              );
            }
          }
        }
      }
    }

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termProgramClass($basic = NULL) {
    $output = $this->termStandardJson(13, 'TermProgramClassInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termProgramType($basic = NULL) {
    $output = $this->termStandardJson(12, 'TermProgramTypeInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termProvince($basic = NULL) {
    $output = $this->termStandardJson(8, 'TermProvinceInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termQuestionField($basic = NULL) {
    $output = $this->termStandardJson(3, 'TermQuestionFieldInfo', $basic);
    return $output;
  }
  /**
   * @return Term Array data
   */
  public function termQuestionLabel($basic = NULL) {
    $output = $this->termStandardJson(5, 'TermQuestionLabelInfo', $basic);
    return $output;
  }
  /**
   * @return Term Array data
   */
  public function termQuestionLibrary($basic = NULL) {
    $output = $this->termStandardJson(4, 'TermQuestionLibraryInfo', $basic);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function termTherapeuticArea() {
    $output = $this->termStandardJson(15, 'TermQuestionLibInfo');
    return $output;
  }

  /** - - - - - Page Query Widget Json- - - - - - - - - - - - - - -   */
  /**
   * @return Term Array data
   */
  public function pageWidgets($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $NodeQuery = new NodeQuery();

    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    // Accredited & OLA
    $acc_meetings = $NodeQuery->meetingNidsByTermType(array(74), $meetings);
    $ola_meetings = $NodeQuery->meetingNidsByTermType(array(75), $meetings);

    $evaluations = $NodeQuery->evaluationNidsByMeeting($meetings);
    $acc_evaluations = $NodeQuery->evaluationNidsByMeeting($acc_meetings);
    $ola_evaluations = $NodeQuery->evaluationNidsByMeeting($ola_meetings);

    $EvaluationFieldQuery = new EvaluationFieldQuery();
    $question_8_answer_set = $EvaluationFieldQuery->questionFieldValues($evaluations, 8, 64);
    $acc_question_8_answer_set = $EvaluationFieldQuery->questionFieldValues($acc_evaluations, 8, 64);
    $ola_question_8_answer_set = $EvaluationFieldQuery->questionFieldValues($ola_evaluations, 8, 64);

    $output = array(
      'class' => array('font-size-12'),
      'type' => 'widget',
      'value' => array(
        array(
          'title' => t('Total Programs'),
          'value' => count($meetings),
          'bgColorClass1' => 'bg-00a9e0',
          'bgColorClass2' => 'bg-05d23e',
          'subLabel1' => t('Accredited'),
          'subValue1' => count($acc_meetings),
          'subLabel2' => t('OLA'),
          'subValue2' => count($ola_meetings),
        ),
        array(
          'title' => t('Evaluations Attendees'),
          'value' => intval(BasicClass::arraySum($NodeQuery->meetingFieldValueArray('signatures', $meetings))),
          'bgColorClass1' => 'bg-00a9e0',
          'bgColorClass2' => 'bg-05d23e',
          'subLabel1' => t('Accredited'),
          'subValue1' => intval(BasicClass::arraySum($NodeQuery->meetingFieldValueArray('signatures', $acc_meetings))),
          'subLabel2' => t('OLA'),
          'subValue2' => intval(BasicClass::arraySum($NodeQuery->meetingFieldValueArray('signatures', $ola_meetings))),
        ),
        array(
          'title' => t('Evaluations Recieved'),
          'value' => count($evaluations),
          'bgColorClass1' => 'bg-00a9e0',
          'bgColorClass2' => 'bg-05d23e',
          'subLabel1' => t('Accredited'),
          'subValue1' => count($NodeQuery->evaluationNidsByMeeting($acc_meetings)),
          'subLabel2' => t('OLA'),
          'subValue2' => count($NodeQuery->evaluationNidsByMeeting($ola_meetings)),
        ),
        array(
          'title' => t('Audience Speaker Rate'),
          'value' => number_format(BasicClass::arrayAverage($question_8_answer_set), 2),
          'bgColorClass1' => 'bg-00a9e0',
          'bgColorClass2' => 'bg-05d23e',
          'subLabel1' => t('Accredited'),
          'subValue1' => number_format(BasicClass::arrayAverage($acc_question_8_answer_set), 2),
          'subLabel2' => t('OLA'),
          'subValue2' => number_format(BasicClass::arrayAverage($ola_question_8_answer_set), 2),
        ),
      ),
    );

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function pageWidgets2($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = array(
      'class' => array('font-size-12'),
      'type' => 'widget2',
      'value' => array(
        array(
          'title' => NULL,
          'column' => 4,
          'bgColorClass1' => 'bg-ffffff',
          'bgColorClass2' => 'bg-ffffff',
          'subLabel1' => t('RESPONSES'),
          'subValue1' => 8750,
          'subLabel2' => t('VERY EFFECTIVE OR EFFECTIVE'),
          'subValue2' => '93%',
        ),
        array(
          'title' => NULL,
          'column' => 4,
          'bgColorClass1' => 'bg-ffffff',
          'bgColorClass2' => 'bg-ffffff',
          'subLabel1' => t('RESPONSES'),
          'subValue1' => 7438,
          'subLabel2' => t('VERY EFFECTIVE OR EFFECTIVE'),
          'subValue2' => '92%',
        ),
        array(
          'title' => NULL,
          'column' => 4,
          'bgColorClass1' => 'bg-ffffff',
          'bgColorClass2' => 'bg-ffffff',
          'subLabel1' => t('RESPONSES'),
          'subValue1' => 3450,
          'subLabel2' => t('VERY EFFECTIVE OR EFFECTIVE'),
          'subValue2' => '91%',
        ),
      ),
    );

    return $output;
  }


  /**
   * @return Term Array data
   */
  public function pageCharts($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $NodeQuery = new NodeQuery();

    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);
    $evaluations = $NodeQuery->evaluationNidsByMeeting($meetings);

    // TermProgram
    $TermProgramQuery = new TermProgramQuery();

    // Accredited & OLA
    $acc_meetings = $NodeQuery->meetingNidsByTermType(array(74), $meetings);
    $ola_meetings = $NodeQuery->meetingNidsByTermType(array(75), $meetings);

    // Evaluation
    $EvaluationFieldQuery = new EvaluationFieldQuery();
    $question_8_answer_set = $EvaluationFieldQuery->questionFieldValues($evaluations, 8, 64);
    $question_8_count = BasicClass::arrayCountValuesBySpecifyArray($question_8_answer_set, array(1, 2, 3, 4, 5));

    $question_5_answer_set = $EvaluationFieldQuery->questionFieldValues($evaluations, 5, 64);
    $question_5_count = BasicClass::arrayCountValuesBySpecifyArray($question_5_answer_set, array(1, 2, 3, 4, 5));

    $output = array(
      array(
        'caption' => t('Accredited Vs. OLA Programs'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'doughnut',
            'chartTypeClass' => 'chart-donut',
            'colorClass' => array('#00a9e0', '#05d23e'),
            'data' => array(count($acc_meetings), count($ola_meetings)),
            'legend' => array('Accredited', 'OLA'),
            'title' => '92.86% of participants rate Speaker as Effective or Very Effective',
          ),
        ),
      ),
      array(
        'caption' => t('Business Unit Summary'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'Bar',
            'chartTypeClass' => 'chart-bar',
            'colorClass' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'chartId' => 101,
            'data' => array(
              "labels" => array("Cardiovascular", "Metabolic", "Oncology", "Respirology"),
              "datasets" => array(
                array(
                  "fillColor" => "#00a9e0",
                  "strokeColor" => "#00a9e0",
                  "pointColor" => "#05d23e",
                  "pointStrokeColor" => "#fff",
                  "data" => array(
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(2088), $acc_meetings)),
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(72), $acc_meetings)),
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(2089), $acc_meetings)),
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(2090), $acc_meetings)),
                  ),
                  "title"=> "Accredited",
                ),
                array(
                  "fillColor" => "#05d23e",
                  "strokeColor" => "#05d23e",
                  "pointColor" => "#00a9e0",
                  "pointStrokeColor" => "#fff",
                  "data" => array(
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(2088), $ola_meetings)),
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(72), $ola_meetings)),
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(2089), $ola_meetings)),
                    count($NodeQuery->meetingNidsByPrograms($TermProgramQuery->programTidsByUnit(2090), $ola_meetings)),
                  ),
                  "title"=> "OLA",
                ),
              )
            ),
            'legend' => array('Very Likely', 'Likely', 'Neutral', 'Unlikely', 'Very Unlikely'),
            'title' => '83.29% of participants will Likely or Very Likely make changes',
          ),
        ),
      ),
      array(
        'caption' => t('Speaker Effectiveness') . ' - ' . t('All Programs'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'piechart',
            'chartTypeClass' => 'chart-piechart',
            'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'data' => array($question_8_count[5], $question_8_count[4], $question_8_count[3], $question_8_count[2], $question_8_count[1]),
            'legend' => array('Very Effective', 'Effective', 'Neutral', 'Ineffective',  'Very Ineffective'),
            'title' => '92.86% of report the speaker are Effective or Very Effective',
          ),
        ),
      ),
      array(
        'caption' => t('Likihood of Changing Clinical Practice'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'piechart',
            'chartTypeClass' => 'chart-piechart',
            'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'data' => array($question_5_count[5], $question_5_count[4], $question_5_count[3], $question_5_count[2], $question_5_count[1]),
            'legend' => array('Very Likely', 'Likely', 'Neutral', 'Unlikely',  'Very Unlikely'),
            'title' => '82.86% of HCP\'s are Likely or Very Likely to Change Clinical Practice',
          ),
        ),
      ),
    );

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function pageCharts1($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $NodeQuery = new NodeQuery();

    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);
    $evaluations = $NodeQuery->evaluationNidsByMeeting($meetings);

    // TermProgram
    $TermProgramQuery = new TermProgramQuery();

    // Accredited & OLA
    $acc_meetings = $NodeQuery->meetingNidsByTermType(array(74), $meetings);
    $ola_meetings = $NodeQuery->meetingNidsByTermType(array(75), $meetings);

    // Evaluation
    $EvaluationFieldQuery = new EvaluationFieldQuery();
    $question_8_answer_set = $EvaluationFieldQuery->questionFieldValues($evaluations, 8, 64);
    $question_8_count = BasicClass::arrayCountValuesBySpecifyArray($question_8_answer_set, array(1, 2, 3, 4, 5));
    $question_5_answer_set = $EvaluationFieldQuery->questionFieldValues($evaluations, 5, 64);
    $question_5_count = BasicClass::arrayCountValues($question_5_answer_set);
    $question_5_count = BasicClass::arrayCountValuesBySpecifyArray($question_8_answer_set, array(1, 2, 3, 4, 5));

    $output = array(
      array(
        'caption' => t('Speaker Effectiveness'),
        'captionBgColorClass' => 'bg-ffffff',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 4,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'piechart',
            'chartTypeClass' => 'chart-piechart',
            'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'data' => array($question_8_count[5], $question_8_count[4], $question_8_count[3], $question_8_count[2], $question_8_count[1]),
            'legend' => array('Very Effective', 'Effective', 'Neutral', 'Ineffective',  'Very Ineffective'),
            'title' => '92.86% of report the speaker are Effective or Very Effective',
          ),
        ),
      ),
      array(
        'caption' => t('Clinical Practice Impact'),
        'captionBgColorClass' => 'bg-ffffff',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 4,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'piechart',
            'chartTypeClass' => 'chart-piechart',
            'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'data' => array($question_5_count[5], $question_5_count[4], $question_5_count[3], $question_5_count[2], $question_5_count[1]),
            'legend' => array('Very Likely', 'Likely', 'Neutral', 'Unlikely',  'Very Unlikely'),
            'title' => '82.86% of HCP\'s are Likely or Very Likely to Change Clinical Practice',
          ),
        ),
      ),
      array(
        'caption' => t('Overall Satisfaction'),
        'captionBgColorClass' => 'bg-ffffff',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 4,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'piechart',
            'chartTypeClass' => 'chart-piechart',
            'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'data' => array($question_5_count[5], $question_5_count[4], $question_5_count[3], $question_5_count[2], $question_5_count[1]),
            'legend' => array('Excellent', 'Very Good', 'Good', 'Fair',  'Poor'),
            'title' => '82.86% of HCP\'s are Likely or Very Likely to Change Clinical Practice',
          ),
        ),
      ),
    );

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function pageCharts2($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = array(
      array(
        'caption' => t('The program was non-biased'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'gauge',
            'chartTypeClass' => 'chart-gauge',
            'colorClass' => array('#00a9e0', '#05d23e'),
            'data' => 0.82,
            'legend' => array('Accredited', 'OLA'),
            'title' => '82%'  . t('Agree or Strongly Agree'),
          ),
        ),
      ),
      array(
        'caption' => t('The program was well organized'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'gauge',
            'chartTypeClass' => 'chart-gauge',
            'colorClass' => array('#00a9e0', '#05d23e'),
            'data' => 0.88,
            'legend' => array('Accredited', 'OLA'),
            'title' => '88%'  . t('Agree or Strongly Agree'),
          ),
        ),
      ),
      array(
        'caption' => t('There was adequate time discussion'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'piechart',
            'chartTypeClass' => 'chart-piechart',
            'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'data' => array(73, 54, 32, 11, 2),
            'legend' => array('Strongly Agree', 'Agree', 'Neutral', 'Disagree',  'Strongly Disagree'),
            'title' => '72%'  . t('Agree or Strongly Agree'),
          ),
        ),
      ),
      array(
        'caption' => t('The program met my learning expectations'),
        'captionBgColorClass' => 'bg-344a5f',
        'captionColor' => array('#344a5f', '#56bfb5', '#f24b99', '#bfbfbf', '#e6e6e6'),
        'captionLegend' => '',
        'captionTitle' => '',
        'column' => 6,
        'chartGroup' => '1',
        'charts' => array(
          array(
            'chartType' => 'piechart',
            'chartTypeClass' => 'chart-piechart',
            'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
            'data' => array(73, 54, 32, 11, 2),
            'legend' => array('Strongly Agree', 'Agree', 'Neutral', 'Disagree',  'Strongly Disagree'),
            'title' => '72%'  . t('Agree or Strongly Agree'),
          ),
        ),
      ),
    );

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function timeGeographyCharts($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $NodeQuery = new NodeQuery();

    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    // Accredited & OLA
    $acc_meetings = $NodeQuery->meetingNidsByTermType(array(74), $meetings);
    $ola_meetings = $NodeQuery->meetingNidsByTermType(array(75), $meetings);

    $output = array(
      'programByMonth' => array(
        'chartId' => '100',
        'chartType' => 'Line',
        'chartData' => array(
          "labels" => array("JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"),
          "datasets" => array(
            array(
              "fillColor" => "rgba(151,187,205,0)",
              "strokeColor" => "#00a9e0",
              "pointColor" => "#05d23e",
              "pointStrokeColor" => "#fff",
              "data" => array(
                count($NodeQuery->meetingNidsByMonth(array(1), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(2), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(3), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(4), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(5), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(6), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(7), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(8), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(9), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(10), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(11), $acc_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(12), $acc_meetings)),
              ),
              "title"=> t("Accredited"),
            ),
            array(
              "fillColor" => "rgba(151,187,205,0)",
              "strokeColor" => "#05d23e",
              "pointColor" => "#00a9e0",
              "pointStrokeColor" => "#fff",
              "data" => array(
                count($NodeQuery->meetingNidsByMonth(array(1), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(2), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(3), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(4), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(5), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(6), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(7), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(8), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(9), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(10), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(11), $ola_meetings)),
                count($NodeQuery->meetingNidsByMonth(array(12), $ola_meetings)),
              ),
              "title"=> t("OLA"),
            ),
          )
        ),
      ),
      'programByRegion' => array(
        'chartId' => '102',
        'chartType' => 'HorizontalBar',
        'chartData' => array(
          "labels" => array( "R1", "R2", "R3"),
          "datasets" => array(
            array(
              "fillColor" => "#00a9e0",
              "strokeColor" => "#00a9e0",
              "pointColor" => "#05d23e",
              "pointStrokeColor" => "#fff",
              "data" => array(
                count($NodeQuery->meetingNidsByProvince(array(20, 19, 30, 21), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(27, 22, 28, 25, 23), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(29), $acc_meetings)),
              ),
              "title"=> t("Accredited"),
            ),
            array(
              "fillColor" => "#05d23e",
              "strokeColor" => "#05d23e",
              "pointColor" => "#00a9e0",
              "pointStrokeColor" => "#fff",
              "data" => array(
                count($NodeQuery->meetingNidsByProvince(array(20, 19, 30, 21), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(27, 22, 28, 25, 23), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(29), $ola_meetings)),
              ),
              "title"=> t("OLA"),
            ),
          )
        ),
      ),
      'programByProvince' => array(
        'chartId' => '103',
        'chartType' => 'Bar',
        'chartData' => array(
          "labels" => array("BC","AB","SK","MB","ON","QC","NB","PEI","NS","NL"),
          "datasets" => array(
            array(
              "fillColor" => "#00a9e0",
              "strokeColor" => "#00a9e0",
              "pointColor" => "#05d23e",
              "pointStrokeColor" => "#fff",
              "data" => array(
                count($NodeQuery->meetingNidsByProvince(array(20), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(19), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(30), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(21), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(27), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(29), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(22), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(28), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(25), $acc_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(23), $acc_meetings)),
              ),
              "title"=> t("Accredited"),
            ),
            array(
              "fillColor" => "#05d23e",
              "strokeColor" => "#05d23e",
              "pointColor" => "#00a9e0",
              "pointStrokeColor" => "#fff",
              "data" => array(
                count($NodeQuery->meetingNidsByProvince(array(20), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(19), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(30), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(21), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(27), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(29), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(22), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(28), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(25), $ola_meetings)),
                count($NodeQuery->meetingNidsByProvince(array(23), $ola_meetings)),
              ),
              "title"=> t("OLA"),
            ),
          )
        ),
      ),
    );

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function timeGeographyCharts2($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $NodeQuery = new NodeQuery();

    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    // Accredited & OLA
    $acc_meetings = $NodeQuery->meetingNidsByTermType(array(74), $meetings);
    $ola_meetings = $NodeQuery->meetingNidsByTermType(array(75), $meetings);

    $output = NULL;
    $output = array(
      'overall' => array(
        'chartId' => '100',
        'chartType' => 'column',
        'chartData' => array(
          "labels" => array('Strongly Agree', 'Agree', 'Neutral', 'Disagree',  'Strongly Disagree'),
          "datasets" => array(
            array(
              'chartType' => 'column',
              'chartTypeClass' => 'chart-column',
              'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
              'data' => array(73, 54, 32, 11, 2),
              'legend' => array('Strongly Agree', 'Agree', 'Neutral', 'Disagree',  'Strongly Disagree'),
              'title' => t('I have a greater awareness of the number of symptomatic asthma patients in my practice'),
            ),
            array(
              'chartType' => 'column',
              'chartTypeClass' => 'chart-column',
              'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
              'data' => array(73, 54, 32, 11, 2),
              'legend' => array('Strongly Agree', 'Agree', 'Neutral', 'Disagree',  'Strongly Disagree'),
              'title' => t('I have a greater awareness of the number of symptomatic asthma patients in my practice'),
            ),
            array(
              'chartType' => 'column',
              'chartTypeClass' => 'chart-column',
              'colorClass' => array('#00a9e0', '#05d23e', '#f24b99', '#bfbfbf', '#e6e6e6'),
              'data' => array(73, 54, 32, 11, 2),
              'legend' => array('Strongly Agree', 'Agree', 'Neutral', 'Disagree',  'Strongly Disagree'),
              'title' => t('I have greater confidence in using a LAMA as add on to ICS/LABA for asthma patients who are symptomatic'),
            ),
          )
        ),
      ),

      'programByRegion' => array(
        'chartId' => '102',
        'chartType' => 'HorizontalBar',
        'chartData' => array(
          "labels" => array( "R1", "R2", "R3"),
          "datasets" => array(
            array(
              "fillColor" => "#00a9e0",
              "strokeColor" => "#00a9e0",
              "pointColor" => "#05d23e",
              "pointStrokeColor" => "#fff",
              "data" => array(
                23,
                76,
                12,
              ),
              "title"=> t("Accredited"),
            ),
            array(
              "fillColor" => "#05d23e",
              "strokeColor" => "#05d23e",
              "pointColor" => "#00a9e0",
              "pointStrokeColor" => "#fff",
              "data" => array(
                80,
                180,
                62,
              ),
              "title"=> t("OLA"),
            ),
          )
        ),
      ),
      'programByProvince' => array(
        'chartId' => '103',
        'chartType' => 'Bar',
        'chartData' => array(
          "labels" => array("BC","AB","SK","MB","ON","QC","NB","PEI","NS","NL"),
          "datasets" => array(
            array(
              "fillColor" => "#00a9e0",
              "strokeColor" => "#00a9e0",
              "pointColor" => "#05d23e",
              "pointStrokeColor" => "#fff",
              "data" => array(
                15,
                9,
                10,
                11,
                17,
                19,
                12,
                18,
                15,
                13,
              ),
              "title"=> t("Accredited"),
            ),
            array(
              "fillColor" => "#05d23e",
              "strokeColor" => "#05d23e",
              "pointColor" => "#00a9e0",
              "pointStrokeColor" => "#fff",
              "data" => array(
                25,
                19,
                30,
                21,
                27,
                29,
                22,
                28,
                25,
                23,
              ),
              "title"=> t("OLA"),
            ),
          )
        ),
      ),
    );

    return $output;
  }

  /** - - - - - Query Table Json- - - - - - - - - - - - - - - - - - - - -   */
  /**
   * @return Term Array data
   */
  public function tableTopRatedSpeakers($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $UserQuery = new UserQuery();
    $user_uids = $UserQuery->allUserUidByRole(array(6));

    $NodeQuery = new NodeQuery();
    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    if (is_array($user_uids) && is_array($meetings)) {
      $users = user_load_multiple($user_uids);
      foreach ($users as $key => $user) {
        $meeting_nids_by_user = $NodeQuery->meetingNidsBySpeakers(array($user->uid), $meetings);

        if (count($meeting_nids_by_user) > 0) {
          $UserInfo = new UserInfo($user->uid);
          $output[] = array(
            'userName' => $UserInfo->userName(),
            'eventNumber' => count($meeting_nids_by_user),
            'evaluationNumber' => intval(BasicClass::arraySum($NodeQuery->meetingFieldValueArray('signatures', $meeting_nids_by_user)) * rand(5, 10) / 10),
            'participantNumber' => BasicClass::arraySum($NodeQuery->meetingFieldValueArray('signatures', $meeting_nids_by_user)),
            'rateScore' => $UserInfo->randNum(30, 50) / 10,
          );
        }
      }
    }

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function tableEventTracker($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $NodeQuery = new NodeQuery();
    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    if (is_array($meetings)) {
      foreach ($meetings as $key => $nid) {
        if (isset($nid)) {
          $MeetingInfo = new MeetingInfo($nid);
          $eventStatus = $MeetingInfo->eventStatus();

          $output[] = array(
            'date' => $MeetingInfo->dateValue(),
            'programName' => $MeetingInfo->programName(),
            'speakerName' => $MeetingInfo->speakerName(),
            'repName' => $MeetingInfo->repName(),
            'city' => $MeetingInfo->cityName(),
            'province' => $MeetingInfo->provinceNameAbbr(),
            'eventStatus' => $eventStatus,
            'eventStatusColor' => $MeetingInfo->eventStatusColor($eventStatus),
          );
        }
      }
    }

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function tableTopAccreditedProgram($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $NodeQuery = new NodeQuery();
    $all_meetings = $NodeQuery->meetingNidsByTime($NodeQuery->meetingNids(), $start_time, $end_time);
    $meetings = $NodeQuery->meetingNidsByPrograms($program_tids, $all_meetings);

    // not use taxonomy_get_tree(), use parameters $program_tids
    $terms = taxonomy_get_tree(2);
    /**
     * only filter current program_tids
     */

    if (is_array($meetings)) {
      if (count($meetings) > 0) {
        if (is_array($terms)) {
          foreach ($terms as $key => $term) {
            $meeting_nids_by_term = $NodeQuery->meetingNidsByPrograms(array($term->tid), $meetings);

            if (count($meeting_nids_by_term) > 0) {
              $TermInfo = new TermInfo($term->tid);

              $output[] = array(
                'programName' => $TermInfo->termName(),
                'eventNumber' => count($meeting_nids_by_term),
                'evaluationNumber' => intval(BasicClass::arraySum($NodeQuery->meetingFieldValueArray('signatures', $meeting_nids_by_term)) * rand(5, 10) / 10),
                'participantNumber' => BasicClass::arraySum($NodeQuery->meetingFieldValueArray('signatures', $meeting_nids_by_term)),
                'ntsScore' => '+' . rand(10, 70),
              );
            }

          }
        }
      }
    }

    return $output;
  }

  /** - - - - - User - - - - - - -- - - - - - - - - - - - - - - - - - - -   */
  /**
   * @return Term Array data
   */
  public function userBasicInfo($uids = NULL) {
    $output = NULL;

    if (is_array($uids)) {
      foreach ($uids as $uid) {
        $UserInfo = new UserInfo($uid);
        $output[] = $UserInfo->basicMethodsValue();
      }
    }

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function userFullInfo($uids = NULL) {
    $output = NULL;

    if (is_array($uids)) {
      foreach ($uids as $uid) {
        $UserInfo = new UserInfo($uid);
        $output[] = $UserInfo->allMethodsValue();
      }
    }

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function allUserList() {
    $output = NULL;

    $UserQuery = new UserQuery();
    $uids = $UserQuery->allUserUid();

    $output = $this->userBasicInfo($uids);

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function speakerUserList() {
    $output = NULL;

    $UserQuery = new UserQuery();
    $uids = $UserQuery->allUserUidByRole(array(6));

    $output = $this->userBasicInfo($uids);

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function repUserList() {
    $output = NULL;

    $UserQuery = new UserQuery();
    $uids = $UserQuery->allUserUidByRole(array(8));

    $output = $this->userBasicInfo($uids);

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function userProfileFields($uid = NULL) {
    $output = NULL;
    $fields = NULL;

    $UserInfo = new UserInfo($uid);

    $fields[] = array(
      'fieldName' => 'field_user_first_name',
      'title' => t('First Name'),
      'type' => 'textfield',
      'defaultValue' => $UserInfo->firstName(),
      'updateStatus' => 0,
      'disabled' => FALSE,
      'required' => FALSE,
    );
    $fields[] = array(
      'fieldName' => 'field_user_last_name',
      'title' => t('Last Name'),
      'type' => 'textfield',
      'defaultValue' => $UserInfo->lastName(),
      'updateStatus' => 0,
      'disabled' => FALSE,
      'required' => FALSE,
    );
    $fields[] = array(
      'fieldName' => 'mail',
      'title' => t('Email'),
      'type' => 'textfield',
      'defaultValue' => $UserInfo->userEmail(),
      'updateStatus' => 0,
      'disabled' => FALSE,
      'required' => FALSE,
    );
    $fields[] = array(
      'fieldName' => 'pass',
      'title' => t('Password'),
      'type' => 'textfield',
      'defaultValue' => NULL,
      'updateStatus' => 0,
      'disabled' => FALSE,
    );
    $fields[] = array(
      'fieldName' => 'field_user_province',
      'title' => t('Province'),
      'type' => 'select',
      'defaultValue' => $UserInfo->provinceTid(),
      'updateStatus' => 0,
      'disabled' => FALSE,
      'required' => FALSE,
      'options' => $this->pushDefaultValue($this->termProvince(TRUE), array('termTid' => NULL, 'termName' => t('Select'))),
    );
    $fields[] = array(
      'fieldName' => 'field_user_city',
      'title' => t('City'),
      'type' => 'select',
      'defaultValue' => $UserInfo->cityTid(),
      'updateStatus' => 0,
      'disabled' => FALSE,
      'required' => FALSE,
      'options' => $this->pushDefaultValue($this->termCity(TRUE), array('termTid' => NULL, 'termName' => t('Select'))),
    );
    $fields[] = array(
      'fieldName' => 'field_user_program_unit',
      'title' => t('Business Unit'),
      'type' => 'select',
      'defaultValue' => $UserInfo->programUnitTids(),
      'updateStatus' => 0,
      'disabled' => FALSE,
      'required' => FALSE,
      'options' => $this->pushDefaultValue($this->termBusinessUnit(TRUE), array('termTid' => NULL, 'termName' => t('Select'))),
    );

    $output = $fields;

    return $output;
  }
}

/**
 * class
   $JsonData = new JsonData();
   $JsonData->sourceArrayData();
 *
 */
class JsonData extends JsonDataUnit  {
  /** - - - - - - node - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return Term Array data
   */
  public function jsonNodeEventList($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output['nodeEventList'] = $this->nodeEventList($program_tids, $start_time, $end_time);

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function jsonNodeMeetingMap($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = $this->nodeMeetingMap($program_tids, $start_time, $end_time);
    return $output;
  }

  /**
   * @return Term Array data
   */
  public function nodeMeetingCreate($program_tid = NULL) {
    $output = NULL;

    $output['evaluationForm'] = $this->termEvaluationForm();
    $output['businessUnitTree'] = $this->termBusinessUnitTree();
    $output['meetingType'] = $this->termMeetingType();
    $output['meetingReceived'] = $this->termMeetingReceived();
    $output['multiTherape'] = $this->termMultiTherape();
    $output['program'] = $this->termProgram();
    $output['programClass'] = $this->termProgramClass();
    $output['programType'] = $this->termProgramType();
    $output['programTree'] = $this->termProgramTree();
    $output['speakerUserList'] = $this->speakerUserList();
    $output['repUserList'] = $this->repUserList();

    return $output;
  }

  /** - - - - - - page - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return Term Array data
   */
  public function jsonPageLanding($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output = $this->jsonProgramUnit($program_tids, $start_time, $end_time);

    return $output;
  }

  /** - - - - - - Program - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return Term Array data
   */
  public function jsonProgramArea($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output = $this->jsonProgramUnit($program_tids, $start_time, $end_time);

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function jsonProgramAreaType($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output['pageWidgets'] = $this->pageWidgets($program_tids, $start_time, $end_time);
    $output['pageCharts'] = $this->pageCharts1($program_tids, $start_time, $end_time);
    $output['pageWidgets2'] = $this->pageWidgets2($program_tids, $start_time, $end_time);
    $output['timeGeographyCharts'] = $this->timeGeographyCharts2($program_tids, $start_time, $end_time);
    $output['pageCharts2'] = $this->pageCharts2($program_tids, $start_time, $end_time);

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function jsonProgramTable($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output['tableEventTracker'] = $this->tableEventTracker($program_tids, $start_time, $end_time);
    $output['tableSpeakerEvaluations'] = $this->tableEventTracker($program_tids, $start_time, $end_time);
    $output['tableTopRatedSpeakers'] = $this->tableTopRatedSpeakers($program_tids, $start_time, $end_time);
    $output['tableTopAccreditedProgram'] = $this->tableTopAccreditedProgram($program_tids, $start_time, $end_time);

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function jsonProgramUnit($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output['pageWidgets'] = $this->pageWidgets($program_tids, $start_time, $end_time);
    $output['pageCharts'] = $this->pageCharts($program_tids, $start_time, $end_time);
    $output['timeGeographyCharts'] = $this->timeGeographyCharts($program_tids, $start_time, $end_time);
    $output['tableTopRatedSpeakers'] = $this->tableTopRatedSpeakers($program_tids, $start_time, $end_time);
    $output['tableTopAccreditedProgram'] = $this->tableTopAccreditedProgram($program_tids, $start_time, $end_time);

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function jsonProgramUnitProgram($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output['pageWidgets'] = $this->pageWidgets($program_tids, $start_time, $end_time);
    $output['tableTopAccreditedProgram'] = $this->tableTopAccreditedProgram($program_tids, $start_time, $end_time);

    return $output;
  }


  /** - - - - - - program is special term - - - - - - - - - - - - - - - - -  */
  /**
   * @return Term Array data
   */
  public function programData($program_tids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    $output['brand'] = $this->termBrand();
    $output['businessUnit'] = $this->termBusinessUnit();
    $output['businessUnitTree'] = $this->termBusinessUnitTree();
    $output['evaluationForm'] = $this->termEvaluationForm();
    $output['programClass'] = $this->termprogramClass();
    $output['programType'] = $this->termProgramType();
    $output['therapeuticArea'] = $this->termTherapeuticArea();

    return $output;
  }

  /** - - - - - - term - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return Term Array data
   */
  public function termQuestionFieldCreate() {
    $output = NULL;

    $output['questionField'] = $this->termQuestionField($basic = TRUE);
    $output['questionLabel'] = $this->termQuestionLabel($basic = TRUE);

    return $output;
  }

  /**
   * @return Term Array data
   */
  public function questionLibrary() {
    $output = NULL;

    $output['questionLibrary'] = $this->termQuestionLibrary();

    return $output;
  }

  /** - - - - - - user - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return Term Array data
   */
  public function jsonUserList() {
    $output = NULL;

    $output['userList'] = $this->allUserList();
    $output['termBusinessUnit'] = $this->termBusinessUnit();
    $output['termCity'] = $this->termCity();
    $output['termProvince'] = $this->termProvince();
    $output['termTherapeuticArea'] = $this->termTherapeuticArea();

    return $output;
  }
  /**
   * @return Term Array data
   */
  public function jsonUserProfile($uid = NULL) {
    $output = NULL;
    $output = $this->userProfileFields($uid);

    return $output;
  }

}
