<?php
/**
 * @file
 * Default views hook.
 */

/**
 * Implements hook_views_default_views().
 */
function islandora_macho_man_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'macho_man';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'islandora_solr';
  $view->human_name = 'Macho Man';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Macho Man';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Islandora Solr: PID */
  $handler->display->display_options['fields']['PID']['id'] = 'PID';
  $handler->display->display_options['fields']['PID']['table'] = 'islandora_solr';
  $handler->display->display_options['fields']['PID']['field'] = 'PID';
  $handler->display->display_options['fields']['PID']['link_to_object'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<img src="islandora/object/[PID]/datastream/TN/view"/>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Filter criterion: Islandora Solr: RELS_EXT_isMemberOfCollection_uri_ms */
  $handler->display->display_options['filters']['RELS_EXT_isMemberOfCollection_uri_ms']['id'] = 'RELS_EXT_isMemberOfCollection_uri_ms';
  $handler->display->display_options['filters']['RELS_EXT_isMemberOfCollection_uri_ms']['table'] = 'islandora_solr';
  $handler->display->display_options['filters']['RELS_EXT_isMemberOfCollection_uri_ms']['field'] = 'RELS_EXT_isMemberOfCollection_uri_ms';
  $handler->display->display_options['filters']['RELS_EXT_isMemberOfCollection_uri_ms']['value'] = 'info:fedora/machoman:collection';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'macho-man';
  $translatables['macho_man'] = array(
    t('Master'),
    t('Macho Man'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('PID'),
    t('<img src="islandora/object/[PID]/datastream/TN/view"/>'),
    t('Page'),
  );
  $views['islandora_solution_pack_macho_man_child_view'] = $view;

  $view = new view();
  $view->name = 'macho_man_contextual';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'islandora_solr';
  $view->human_name = 'Macho Man Contextual';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Macho Man Contextual';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Islandora Solr: mods_subject_topic_ms */
  $handler->display->display_options['fields']['mods_subject_topic_ms']['id'] = 'mods_subject_topic_ms';
  $handler->display->display_options['fields']['mods_subject_topic_ms']['table'] = 'islandora_solr';
  $handler->display->display_options['fields']['mods_subject_topic_ms']['field'] = 'mods_subject_topic_ms';
  $handler->display->display_options['fields']['mods_subject_topic_ms']['label'] = 'Topics';
  $handler->display->display_options['fields']['mods_subject_topic_ms']['link_to_object'] = 0;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['null']['default_argument_options']['index'] = '2';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['null']['validate_options']['code'] = 'module_load_include(\'inc\', \'islandora\', \'includes/utilities\');
$object = islandora_object_load($argument);
if ($object) {
  $namespace = islandora_get_namespace($argument);
  if ($namespace == \'machoman\') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}
else {
  return FALSE;
}
';
  /* Contextual filter: Islandora Solr: PID */
  $handler->display->display_options['arguments']['PID']['id'] = 'PID';
  $handler->display->display_options['arguments']['PID']['table'] = 'islandora_solr';
  $handler->display->display_options['arguments']['PID']['field'] = 'PID';
  $handler->display->display_options['arguments']['PID']['default_action'] = 'default';
  $handler->display->display_options['arguments']['PID']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['PID']['default_argument_options']['index'] = '2';
  $handler->display->display_options['arguments']['PID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['PID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['PID']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['macho_man_contextual'] = array(
    t('Master'),
    t('Macho Man Contextual'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Topics'),
    t('All'),
    t('Block'),
  );

  $views['islandora_solution_pack_macho_man_contextual_block'] = $view;
  return $views;
}
