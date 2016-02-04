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

