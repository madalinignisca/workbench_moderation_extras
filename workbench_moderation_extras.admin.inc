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

  // var to keep multiple options
  $options = array();

  // Get possible node types (must have moderation enabled on them)
  $node_types = node_type_get_types();
  foreach ($node_types as $node_type) {
    if (workbench_moderation_node_type_moderated($node_type->type)) {
      $options['types'][$node_type->type] = $node_type->name;
    }
  }

  $form['workbench_moderation_extras_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select moderated node types'),
    '#options' => $options['types'],
  );

  // Get users to receive emails
  // This should be a multi entry field like on "Mentors" list on Drupal.org

  // Set which state to be used for notifications

  // Set the amount of time for a state to become invalid in seconds
  $form['workbench_moderation_extras_time'] = array(
    '#type' => 'textfield',
    '#title' => 'How many seconds until a Published must change state?',
    '#default_value' => 3600 * 24 * 28, // 4 weeks
    '#maxlength' => 16
  );

  $form['#submit'][] = 'workbench_moderation_extras_admin_settings_submit';

  return system_settings_form($form);
}

