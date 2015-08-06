<?php
/**
 * @file
 * Admin form for the Macho man.
 */

/**
 * Admin settings form for the solution pack.
 *
 * @param array $form
 *   An array representing a form within Drupal.
 * @param array $form_state
 *   An array containing the Drupal form state.
 */
function islandora_macho_man_admin_form($form, $form_state) {
  $form['islandora_macho_man_restrict_namespace'] = array(
    '#type' => 'checkbox',
    '#title' => t('Restrict searches to within the machoman namespace'),
    '#default_value' => variable_get('islandora_macho_man_restrict_namespace', FALSE),
    '#description' => t('hook_islandora_solr_query()'),
  );
  $form['islandora_macho_man_force_label_only'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force the display of the results to only show the label'),
    '#default_value' => variable_get('islandora_macho_man_force_label_only', FALSE),
    '#description' => t('hook_islandora_solr_query_alter()'),
  );
  $form['islandora_macho_man_object_url_params'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force the addition of params to the object URL link for demo purposes'),
    '#default_value' => variable_get('islandora_macho_man_object_url_params', FALSE),
    '#description' => t('hook_islandora_solr_results_alter()'),
  );
  $form['islandora_macho_man_spinning_thumbs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force every thumbnail to be a spinning Macho Man'),
    '#default_value' => variable_get('islandora_macho_man_spinning_thumbs', FALSE),
    '#description' => t('hook_islandora_solr_object_result_alter()'),
  );
  return system_settings_form($form);
}
