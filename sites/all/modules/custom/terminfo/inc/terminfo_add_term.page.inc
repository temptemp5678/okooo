<?php
/**
 * @file for Add new term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 */
function _terminfo_add_program() {
  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(2);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $form['actions']['submit']['#prefix'] = '<div class="row text-center clear-both">';
  $form['actions']['submit']['#suffix'] = '</div>';
  $form['actions']['submit']['#attributes']['class'][] = 'margin-top-24';

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $output = drupal_render($form);

  return $output;
}

/**
 * Implements hook_form(), callback from hook_menu()
 */
function _terminfo_add_notify() {
  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(3);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $form['actions']['submit']['#prefix'] = '<div class="row text-center clear-both">';
  $form['actions']['submit']['#suffix'] = '</div>';
  $form['actions']['submit']['#attributes']['class'][] = 'margin-top-24';
  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $output = drupal_render($form);

  return $output;
}
