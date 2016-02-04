<?php
/**
 * @file
 */

/**
 * class
   $NodeQuery = new NodeQuery();
   $NodeQuery->allNotifylogNid();
 *
 */
class NodeQuery {
  /** - - - - - - common - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @parameter, $node_type is array()
   *
   * @return array,
   * all Product NID
   */
  public function specifyBundleNid($node_type = array()) {

    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $node_type)
      ->propertyCondition('status', NODE_PUBLISHED);

    $result = $query->execute();

    $nid_array = NULL;
    if (isset($result['node'])) {
      if (count($result['node']) > 0 ) {
        $nid_array = array_keys($result['node']);
      }
    }

    return $nid_array;
  }

  /** - - - - - - Evaluation - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return array,
   * all Evaluation NID
   */
  public function evaluationNids() {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'evaluation')
      ->propertyCondition('status', NODE_PUBLISHED);

    $result = $query->execute();

    $nid_array = NULL;
    if (isset($result['node'])) {
      if (count($result['node']) > 0 ) {
        $nid_array = array_keys($result['node']);
      }
    }

    return $nid_array;
  }

  /**
   * @parameter array, $meeting_nids
   *
   * @return array,
   * all evaluation NID by specify $meeting_nids
   */
  public function evaluationNidsByMeeting($meeting_nids = array()) {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'evaluation')
      ->propertyCondition('status', NODE_PUBLISHED);

    $nid_array = NULL;
    if (is_array($meeting_nids))  {
      $query->fieldCondition('field_evaluation_meeting', 'target_id', $meeting_nids, 'IN');
      $result = $query->execute();

      if (isset($result['node'])) {
        if (count($result['node']) > 0 ) {
          $nid_array = array_keys($result['node']);
        }
      }
    }

    return $nid_array;
  }

  /** - - - - - - Meeting - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @parameter ,
   *
   * @return array,
   * all Meeting NID
   */
  public function meetingNids() {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'meeting')
      ->propertyCondition('status', NODE_PUBLISHED);

    $result = $query->execute();

    $nid_array = NULL;
    if (isset($result['node'])) {
      if (count($result['node']) > 0 ) {
        $nid_array = array_keys($result['node']);
      }
    }

    return $nid_array;
  }

  /**
   * @parameter
   *  array, meeting nids
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsByMonth($months = array(), $meeting_nids = array()) {
    $output = NULL;

    if (is_array($meeting_nids) && is_array($months)) {
      $nodes = node_load_multiple($meeting_nids);

      if (is_array($nodes)) {
        foreach($nodes as $node) {
          $MeetingInfo = new MeetingInfo($node);
          if (in_array(intval($MeetingInfo->dateValue('n')), $months)) {
            $output[] = $node->nid;
          }
        }
      }
    }

    return $output;
  }

  /**
   * @parameter
   *  array, meeting nids
   *  integer, status tid
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsByPrograms($program_tids = array(), $meeting_nids = array()) {
    $output = NULL;

    if (is_array($program_tids)) {
      if (is_array($meeting_nids)) {
        $nodes = node_load_multiple($meeting_nids);

        if (is_array($nodes)) {
          foreach($nodes as $node) {
            $MeetingInfo = new MeetingInfo($node);

            if (in_array($MeetingInfo->programTid(), $program_tids)) {
              $output[] = $node->nid;
            }
          }
        }
      }
    }

    return $output;
  }

  /**
   * @parameter
   *  array, province_tids
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsByProvince($province_tids = array(), $meeting_nids = array()) {
    $output = NULL;

    if (is_array($province_tids) && is_array($meeting_nids)) {
      foreach($meeting_nids as $nid) {
        $MeetingInfo = new MeetingInfo($nid);

        if(in_array($MeetingInfo->provinceTid(), $province_tids)) {
          $output[] = $nid;
        }
      }
    }

    return $output;
  }

  /**
   * @parameter
   *  array, meeting nids
   *  integer, specify user uid is node author
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsBySpeakers($speaker_uids = array(), $meeting_nids = array()) {
    $output = NULL;

    if (is_array($meeting_nids)) {
      foreach($meeting_nids as $nid) {
        $MeetingInfo = new MeetingInfo($nid);
        if(in_array($MeetingInfo->speakerUid(), $speaker_uids)) {
          $output[] = $nid;
        }
      }
    }

    return $output;
  }

  /**
   * @parameter
   *  array, meeting nids
   *  integer, status tid
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsByStatus($status = array(), $meeting_nids = array()) {
    $output = NULL;

    if (is_array($status)) {
      if (is_array($meeting_nids)) {
        $nodes = node_load_multiple($meeting_nids);

        if (is_array($nodes)) {
          foreach($nodes as $node) {
            $MeetingInfo = new MeetingInfo($node);
            if(in_array($status, $MeetingInfo->statusTid())) {
              $output[] = $node->nid;
            }
          }
        }
      }
    }

    return $output;
  }

  /**
   * @parameter
   *  array, meeting nids
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsByTime($meeting_nids = array(), $start_time = NULL, $end_time = NULL) {
    $output = NULL;

    if ($start_time || $end_time) {
      if (is_array($meeting_nids)) {
        foreach($meeting_nids as $nid) {
          $MeetingInfo = new MeetingInfo($nid);

          if ($start_time) {
            if ($MeetingInfo->dateUnixStamp() > $start_time) {
              if ($end_time) {
                if ($MeetingInfo->dateUnixStamp() < $end_time) {
                  $output[] = $nid;
                }
              }
              else {
                $output[] = $nid;
              }
            }
          }
          else {
            if ($end_time) {
              if ($MeetingInfo->dateUnixStamp() < $end_time) {
                $output[] = $nid;
              }
            }
          }

        }
      }
    }
    else {
      $output = $meeting_nids;
    }

    return $output;
  }

  /**
   * @parameter
   *  array, meeting nids
   *  integer, specify user uid is node author
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsByTermType($program_type_tids = array(), $meeting_nids = array()) {
    $output = NULL;

    if (is_array($program_type_tids) && is_array($meeting_nids)) {
      foreach($meeting_nids as $nid) {
        $MeetingInfo = new MeetingInfo($nid);

        $TermProgramInfo = new TermProgramInfo($MeetingInfo->programTid());

        if (is_array($TermProgramInfo->programTypeTids())) {
          if(array_intersect($program_type_tids, $TermProgramInfo->programTypeTids())) {
            $output[] = $nid;
          }
        }
      }
    }

    return $output;
  }

  /**
   * @parameter
   *  array, meeting nids
   *  integer, specify user uid is node author
   *
   * @return array,
   *  all Meeting NID
   */
  public function meetingNidsByUsers($user_uids = array(), $meeting_nids = array()) {
    $output = NULL;

    if (is_array($meeting_nids)) {
      foreach($meeting_nids as $nid) {
        $MeetingInfo = new MeetingInfo($nid);
        if(in_array($MeetingInfo->nodeUid(), $user_uids)) {
          $output[] = $nid;
        }
      }
    }

    return $output;
  }

  /** - - - - - - Meeting Field Value- - - - - - - - - - - - - - - - - - -  */
  /**
   * @return array,
   */
  public function meetingFieldValueArray($field_method = NULL, $meeting_nids = array()) {
    $output = NULL;

    if (is_array($meeting_nids)) {
      $meeting_nodes = node_load_multiple($meeting_nids);
      foreach ($meeting_nodes as $key => $node) {
        $MeetingInfo = new MeetingInfo($node->nid);
        $output[] = $MeetingInfo->{$field_method}();
      }
    }

    return $output;
  }

}

/**
 * class
   $NodeQuery = new NodeQuery();
   $NodeQuery->allNotifylogNid();
 *
 */
class MeetingFieldQuery {

}


/**
 * class
   $EvaluationFieldQuery = new EvaluationFieldQuery();
   $EvaluationFieldQuery->questionFieldValueArray();
 *
 */
class EvaluationFieldQuery {
  /**
   * @return array,
   */
  public function questionFieldValues($evaluation_nids = array(), $queslibr_tid = NULL, $quesfield_tid = NULL) {
    $output = NULL;

    if (is_array($evaluation_nids)) {
      $evaluation_nodes = node_load_multiple($evaluation_nids);
      foreach ($evaluation_nodes as $key => $node) {
        $EvaluationInfo = new EvaluationInfo($node->nid);
        $answer_set = $EvaluationInfo->evaluationAnswerSet($evaluation_nids);

        if (is_array($answer_set)) {
          $cc = drupal_array_nested_key_exists($answer_set, array(64));

          foreach ($answer_set as $key => $row) {
            if ($row['answerset_queslibr_tid'] == $queslibr_tid && $row['answerset_quesfield_tid'] == $quesfield_tid) {
              $output[] = $row['answerset_answer'];
            }
          }
        }
      }
    }

    return $output;
  }
}

