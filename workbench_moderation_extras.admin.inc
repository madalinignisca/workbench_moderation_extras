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
    '#default_value' => variable_get('workbench_moderation_extras_node_types'),
  );
  // also if no value, creates a warning in checkbox constructions. please check
  // @TODO We sure need something to check if the node type is taken out of moderation...

  // Get users to receive emails
  // This should be a multi entry field like on "Mentors" list on Drupal.org
  $users = _workbench_moderation_extras_get_allowed_users();
  $options['users'] = array();
  foreach ($users as $user) {
    $options['users'][$user->uid] = $user->name;
  }
  $form['workbench_moderation_extras_users'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select users to receive email notifications'),
    '#options' => $options['users'],
    '#default_value' => variable_get('workbench_moderation_extras_users'),
  );
  if (empty($options['users'])) {
    $form['workbench_moderation_extras_users'] = array(
      '#markup' => t('Please make sure to have users with permission Use "Regular review" workbench tab'),
    );
  }

  // Set the amount of time for a state to become invalid in seconds
  $form['workbench_moderation_extras_time'] = array(
    '#type' => 'textfield',
    '#title' => 'How many seconds until a Published must change state?',
    '#default_value' => variable_get('workbench_moderation_extras_time', 3600 * 24 * 28), // 4 weeks by default
    '#maxlength' => 16
  );

  return system_settings_form($form);
}

// validate and save submitted data
function workbench_moderation_extras_admin_settings_validate($form, &$form_state) {
  if(!is_numeric($form_state['values']['workbench_moderation_extras_time'])) {
    form_set_error('workbench_moderation_extras_time', t('Please enter a number'));
  }
}
