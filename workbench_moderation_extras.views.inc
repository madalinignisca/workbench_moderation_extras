<?php

/**
 * Add Regular review views display to Workbench Moderation
 *
 * @throws \Exception
 */
function _workbench_moderation_extras_views_add_display() {
  $view = views_get_view('workbench_moderation');

  if ($view && !$view->access('regular_review_page')) {
    /* Display: Regular review page */
    $handler = $view->new_display('page', 'Regular review page', 'regular_review_page');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Regular review';
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['defaults']['access'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['access']['perm'] = 'use workbench_moderation regular review tab';
    $handler->display->display_options['defaults']['empty'] = FALSE;
    /* No results behavior: Global: Text area */
    $handler->display->display_options['empty']['area']['id'] = 'area';
    $handler->display->display_options['empty']['area']['table'] = 'views';
    $handler->display->display_options['empty']['area']['field'] = 'area';
    $handler->display->display_options['empty']['area']['content'] = 'This list displays content in the "Regular review" state that you can moderate. Currently there is no such content.';
    $handler->display->display_options['empty']['area']['format'] = 'plain_text';
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Workbench Moderation: Current */
    $handler->display->display_options['filters']['is_current']['id'] = 'is_current';
    $handler->display->display_options['filters']['is_current']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['is_current']['field'] = 'is_current';
    $handler->display->display_options['filters']['is_current']['value'] = '1';
    /* Filter criterion: Workbench Moderation: State */
    $handler->display->display_options['filters']['state']['id'] = 'state';
    $handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['state']['field'] = 'state';
    $handler->display->display_options['filters']['state']['value'] = array(
      'regular_review' => 'regular_review',
    );
    $handler->display->display_options['filters']['state']['expose']['label'] = 'Workbench Moderation: State';
    $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
    $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
    /* Filter criterion: Content: Title */
    $handler->display->display_options['filters']['title']['id'] = 'title';
    $handler->display->display_options['filters']['title']['table'] = 'node';
    $handler->display->display_options['filters']['title']['field'] = 'title';
    $handler->display->display_options['filters']['title']['relationship'] = 'nid';
    $handler->display->display_options['filters']['title']['operator'] = 'contains';
    $handler->display->display_options['filters']['title']['exposed'] = TRUE;
    $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
    $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
    $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
    $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
    $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['relationship'] = 'nid';
    $handler->display->display_options['filters']['type']['exposed'] = TRUE;
    $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
    $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
    $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
    $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
    $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
    $handler->display->display_options['path'] = 'admin/workbench/regular-review';
    $handler->display->display_options['menu']['type'] = 'tab';
    $handler->display->display_options['menu']['title'] = 'Regular review';
    $handler->display->display_options['menu']['weight'] = '99';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;

    $view->save();
  }



}

function _workbench_moderation_extras_views_remove_display() {
  // Could not find yet a way to remove displays pragmatically
  // Directly removing from the database should work
}
