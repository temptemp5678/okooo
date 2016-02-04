<?php
/**
 * @file
 */

/**
 * class
   $TermQuery = new TermQuery();
   $TermQuery->allProgramTid();
 */
class TermQuery {
  /**
   * @parameter ,
   *
   * @return array,
   * all Program TID
   */
  public function programTids() {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'taxonomy_term')
      ->entityCondition('bundle', 'program');
    $result = $query->execute();

    $output = NULL;
    if (isset($result['taxonomy_term'])) {
      if (count($result['taxonomy_term']) > 0 ) {
        $output = array_keys($result['taxonomy_term']);
      }
    }

    return $output;
  }

}

/**
 * class
   $TermProgramQuery = new TermProgramQuery();
   $TermProgramQuery->programTidsByUnit($tid);
   $TermProgramQuery->programTidsByField($program_tids, $field_method = 'programUnitTid', $filter_tids = array(2090));
 */
class TermProgramQuery extends TermQuery {
  /**
   * @parameter , $field_method = 'programUnitTid';
   *
   * @return array,
   * all Program TID
   */
  public function programTidsByField($program_tids = array(), $field_method = NULL, $filter_tids = array()) {
    $output = NULL;

    if (is_array($program_tids)) {
      $terms = taxonomy_term_load_multiple($program_tids);

      foreach ($terms as $key => $term) {
        $TermProgramInfo = new TermProgramInfo($term->tid);

        // return is array
        if (is_array($TermProgramInfo->{$field_method}())) {
          $check_result = array_intersect($TermProgramInfo->{$field_method}(), $filter_tids);

          if (count($check_result) > 0) {
            $output[] = $term->tid;
          }
        }
        // single one
        else {
          if (in_array($TermProgramInfo->{$field_method}(), $filter_tids)) {
            $output[] = $term->tid;
          }
        }
      }
    }

    return $output;
  }

  /** - - - - - - other - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @return array
   * get program_tids by specify unit tid or nation tid
   */
  public function programTidsByUnit($tid = NULL) {
    $program_tids = array();
    $unit_tids = array();

    if ($tid) {
      /**
       * get program tids depend on unit tid or nation tid
       */
      $TermProgramQuery = new TermProgramQuery();
      $all_program_tids = $TermProgramQuery->programTids();

      $term = taxonomy_term_load($tid);
      if ($term) {
        // program nation
        if ($term->vid == 22) {
          $unit_terms = taxonomy_get_tree(11);

          if (is_array($unit_terms)) {
            foreach ($unit_terms as $term_key => $term_row) {
              $unit_tids[] = $term_row->tid;
            }
          }
        }
        // program unit
        elseif ($term->vid == 11){
          $unit_tids[] = $tid;
        }

        $program_tids = $TermProgramQuery->programTidsByField($all_program_tids, $field_method = 'programUnitTid', $filter_tids = $unit_tids);
      }
    }

    return $program_tids;
  }

  /**
   * @return array
   * get program_tids by specify Area tid
   */
  public function programTidsByArea($tid = NULL) {
    $program_tids = array();
    $area_tids = array();

    if ($tid) {
      /**
       * get program tids depend on unit tid or nation tid
       */
      $TermProgramQuery = new TermProgramQuery();
      $all_program_tids = $TermProgramQuery->programTids();

      $term = taxonomy_term_load($tid);
      if ($term) {
        // Therapeutic Area
        if ($term->vid == 15) {
          $area_tids = array($tid);
        }

        $program_tids = $TermProgramQuery->programTidsByField($all_program_tids, $field_method = 'therapAreaTids', $filter_tids = $area_tids);
      }
    }

    return $program_tids;
  }

}
