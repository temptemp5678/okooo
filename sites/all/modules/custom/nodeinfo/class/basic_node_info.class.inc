<?php
/**
 * @file
 */

/**
 * class
   $NodeInfo = new NodeInfo($nid);
   $NodeInfo->nodeTitle();
 */
class NodeInfo {
  protected $nid;
  protected $node = NULL;

  /**
   * @parameter is nid or node object
   */
  function __construct($param){
    if (is_numeric($param)) {
      $node = node_load($param);
      if ($node) {
        $this->node = $node;
        $this->nid = $this->node->nid;
      }
    }
    else if (is_object($param)) {
      if (isset($param->nid)) {
        $this->node = $param;
        $this->nid = $this->node->nid;
      }
    }
  }

  /** - - - - - - field - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  public function entityWrapper() {
    $output = NULL;
    if (isset($this->node->nid)) {
      $output = entity_metadata_wrapper('node', $this->node);
    }
    return $output;
  }

  /** - - - - - - basic - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return String, Node Title
   */
  public function nodeNid() {
    $output = NULL;
    if (isset($this->nid)) {
      $output = $this->nid;
    }
    return $output;
  }

  /**
   * @return String, Node Title
   */
  public function nodeTitle() {
    $output = NULL;
    if (isset($this->node->title)) {
      $output = $this->node->title;
    }
    return $output;
  }

  /**
   * @return String, Node Title
   */
  public function nodeBody() {
    $output = NULL;
    if (isset($this->node->body['und'][0]['value'])) {
      $output = $this->node->body['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return String, Node Title
   */
  public function nodeUid() {
    $output = $this->node->uid;
    return $output;
  }

  /**
   * @return integer, date unix stamp for quote order time
   */
  public function createdUnixStamp() {
    $output = NULL;
    if (isset($this->node->created)) {
      $output = $this->node->created;
    }
    return $output;
  }
  /**
   * @return integer, date unix stamp
   */
  public function createdValue($format = NULL) {
    if (!$format) {
      $format = "Y-m-d";
    }

    $output = NULL;
    $stamp = $this->createdUnixStamp();
    if ($stamp) {
      $output = format_date($stamp, 'custom', $format);
    }
    return $output;
  }

  /** - - - - - - other - - - - - - - - - - - - - - - - - - - - - - - - - -  */

}

/**
 * class
   $MeetingInfo = new MeetingInfo($nid);
   $MeetingInfo->programTid();
 */
class MeetingInfo extends NodeInfo {
  /** - - - - - - field - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  /**
   * @return string,
   */
  public function address() {
    $output = NULL;
    if (isset($this->node->field_meeting_address['und'][0]['value'])) {
      $output = $this->node->field_meeting_address['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return string,
   */
  public function catering() {
    $output = NULL;
    if (isset($this->node->field_meeting_catering['und'][0]['value'])) {
      $output = $this->node->field_meeting_catering['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function cityTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_city['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_city['und'][0]['target_id'];
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
   * @return integer, date unix stamp for quote order time
   */
  public function dateUnixStamp() {
    $output = NULL;
    if (isset($this->node->field_meeting_date['und'][0]['value'])) {
      $output = $this->node->field_meeting_date['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return string depeng on parameter format
   */
  public function dateValue($format = NULL, $timezone = NULL) {
    if (!$format) {
      $format = "Y-m-d";
    }

    $output = NULL;
    $stamp = $this->dateUnixStamp();
    if ($stamp) {
      $output = format_date($stamp, 'custom', $format, $timezone);
    }
    return $output;
  }

  /**
   * @return Integer,
   */
  public function eventStatus() {
    $output = NULL;
    $eventStatus = array('Overdue', 'Upcoming', 'Evaluated', 'In Progress');
    $key = rand(0, 3);
    $output = $eventStatus[$key];

    return $output;
  }
  /**
   * @return Integer,
   */
  public function eventStatusColor($eventStatus = NULL) {
    $output = NULL;

    switch ($eventStatus) {
      case 'Overdue':
        $output = 'bg-f24b99';
        break;
      case 'Upcoming':
        $output = 'bg-00aade';
        break;
      case 'Evaluated':
        $output = 'bg-a5d13f';
        break;
      case 'In Progress':
        $output = 'bg-ffc400';
        break;

      default:
        $output = 'bg-e6e6e6';
        break;
    }

    return $output;
  }

  /**
   * @return string,
   */
  public function foodCost() {
    $output = NULL;
    if (isset($this->node->field_meeting_food_cost['und'][0]['value'])) {
      $output = $this->node->field_meeting_food_cost['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return string,
   */
  public function honorarium() {
    $output = NULL;
    if (isset($this->node->field_meeting_honorarium['und'][0]['value'])) {
      $output = $this->node->field_meeting_honorarium['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return string,
   */
  public function latitude() {
    $output = NULL;
    if (isset($this->node->field_meeting_latlon_lat['und'][0]['value'])) {
      $output = $this->node->field_meeting_latlon_lat['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return string,
   */
  public function longitude() {
    $output = NULL;
    if (isset($this->node->field_meeting_latlon_lon['und'][0]['value'])) {
      $output = $this->node->field_meeting_latlon_lon['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function locationTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_location['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_location['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function locationName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->locationTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function meetingTypeTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_meeting_type['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_meeting_type['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function meetingTypeName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->meetingTypeTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function meetingReceivedTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_received['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_received['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function meetingReceivedName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->meetingReceivedTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function multiTherapeTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_multi_therape['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_multi_therape['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function multiTherapeName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->multiTherapeTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function numberOfEvaluation() {
    $output = NULL;
    $output = 3;

    return $output;
  }

  /**
   * @return string,
   */
  public function postalCode() {
    $output = NULL;
    if (isset($this->node->field_meeting_postal_code['und'][0]['value'])) {
      $output = $this->node->field_meeting_postal_code['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function programTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_program['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_program['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return Integer, Term Tid
   */
  public function programName() {
    $output = NULL;

    $TermInfo = new TermInfo($this->programTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function programEvaluationFormTid() {
    $output = NULL;
    if ($this->programTid()) {
      $TermProgramInfo = new TermProgramInfo($this->programTid());
      $output = $TermProgramInfo->evaluationFormTid();
    }
    return $output;
  }
  /**
   * @return array,
   */
  public function programEvaluationFormArray() {
    $output = NULL;
    if ($this->programEvaluationFormTid()) {
      $TermEvaluationFormInfo = new TermEvaluationFormInfo($this->programEvaluationFormTid());
      $output = $TermEvaluationFormInfo->questionSetArray();
    }
    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function provinceTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_province['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_province['und'][0]['target_id'];
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
   * @return String, Term Property
   */
  public function provinceNameAbbr() {
    $output = NULL;
    $TermProvinceInfo = new TermProvinceInfo($this->provinceTid());
    if(!empty($TermProvinceInfo)) {
      $output = $TermProvinceInfo->provinceNameAbbr();
    }
    return $output;
  }

  /**
   * @return Integer, User Uid
   */
  public function repUid() {
    $output = NULL;
    if (isset($this->node->field_meeting_representative['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_representative['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, User Property
   */
  public function repName() {
    $output = NULL;
    $UserInfo = new UserInfo($this->repUid());
    if(!empty($UserInfo)) {
      $output = $UserInfo->fullname();
    }

    return $output;
  }
  /**
   * @return String, User Property
   */
  public function repEmail() {
    $output = NULL;
    $UserInfo = new UserInfo($this->repUid());
    if(!empty($UserInfo)) {
      $output = $UserInfo->userEmail();
    }

    return $output;
  }

  /**
   * @return Integer,
   */
  public function signatures() {
    $output = NULL;
    if (isset($this->node->field_meeting_signatures['und'][0]['value'])) {
      $output = $this->node->field_meeting_signatures['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return Integer, User Uid
   */
  public function speakerUid() {
    $output = NULL;
    if (isset($this->node->field_meeting_speaker['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_speaker['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, User Property
   */
  public function speakerEmail() {
    $output = NULL;
    $UserInfo = new UserInfo($this->speakerUid());
    if(!empty($UserInfo)) {
      $output = $UserInfo->userEmail();
    }

    return $output;
  }
  /**
   * @return String, User Property
   */
  public function speakerName() {
    $output = NULL;
    $UserInfo = new UserInfo($this->speakerUid());
    if(!empty($UserInfo)) {
      $output = $UserInfo->fullname();
    }

    return $output;
  }
  /**
   * @return String, User Property
   */
  public function speakerLastName() {
    $output = NULL;
    $UserInfo = new UserInfo($this->speakerUid());
    if(!empty($UserInfo)) {
      $output = $UserInfo->lastname();
    }

    return $output;
  }

  /**
   * @return Integer, Term Tid
   */
  public function userGroupTid() {
    $output = NULL;
    if (isset($this->node->field_meeting_user_group['und'][0]['target_id'])) {
      $output = $this->node->field_meeting_user_group['und'][0]['target_id'];
    }
    return $output;
  }
  /**
   * @return String, Term Property
   */
  public function userGroupName() {
    $output = NULL;
    $TermInfo = new TermInfo($this->userGroupTid());
    if(!empty($TermInfo)) {
      $output = $TermInfo->termName();
    }

    return $output;
  }

  /**
   * @return string,
   */
  public function venueName() {
    $output = NULL;
    if (isset($this->node->field_meeting_venue_name['und'][0]['value'])) {
      $output = $this->node->field_meeting_venue_name['und'][0]['value'];
    }
    return $output;
  }

  /** - - - - - - other - - - - - - - - - - - - - - - - - - - - - - - - - -  */

}

/**
 * class
   $EvaluationInfo = new EvaluationInfo($nid);
   $EvaluationInfo->meetingNid();
 */
class EvaluationInfo extends NodeInfo {
  /** - - - - - - field - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  /**
   * @return Integer, meeting Tid
   */
  public function meetingNid() {
    $output = NULL;
    if (isset($this->node->field_evaluation_meeting['und'][0]['target_id'])) {
      $output = $this->node->field_evaluation_meeting['und'][0]['target_id'];
    }
    return $output;
  }

  /**
   * @return Array,
   */
  public function evaluationAnswerSet() {
    $output = NULL;
    if (isset($this->node->field_evaluation_answer_set['und'][0])) {
      $output = $this->node->field_evaluation_answer_set['und'];
    }
    return $output;
  }

  /** - - - - - - other - - - - - - - - - - - - - - - - - - - - - - - - - -  */
}
