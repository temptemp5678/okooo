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


}


