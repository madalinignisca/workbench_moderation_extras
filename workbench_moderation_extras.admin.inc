<?php
/**
 * @file
 * Administrative forms for Workbench Moderation Extras Module.
 */

/**
 * Form builder. Configure Workbench Moderation Extras
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function workbench_moderation_extras_admin_settings() {
  // Get possible node types (must have moderation enabled on them)
  $node_types = node_type_get_types(); // replace with function that gets moderated node types. check workbench api
  foreach ($node_types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }

  // build form elements
  $form['workbench_moderation_extras_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select moderated node types'),
    '#options' => $options,
  );
  $form['#submit'][] = 'workbench_moderation_extras_admin_settings_submit';

  return system_settings_form($form);
}