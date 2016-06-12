<?php

/**
 * Get a list of users that have permissions to access workbench moderation
 *
 * @return array
 */
function _workbench_moderation_extras_get_allowed_users() {
  // our needed permission: 'moderate content from published to regular_review'
  $query = "SELECT DISTINCT u.uid, u.name, u.mail FROM {users} u
LEFT JOIN {users_roles} ur ON u.uid = ur.uid
LEFT JOIN {role_permission} p ON ur.rid = p.rid
WHERE u.uid != 0 AND u.uid != 1 AND (p.permission IS NOT NULL AND
p.permission LIKE '%use workbench_moderation regular review tab%')
ORDER BY u.created DESC";
  return db_query($query)->fetchAllAssoc('uid');
}

/**
 * Send an email to a user for the regular review
 *
 * @param $user
 */
function _workbench_moderation_extras_mail($user) {
  $module = 'workbench_moderation_extras';
  $key = 'regular_review';
  $to = $user['mail'];
  $language = language_default();
  $params = 'Some nodes have expired and need a Regular Review to keep them fresh';
  $from = variable_get('site_mail');
  $send = TRUE;

  drupal_mail($module, $key, $to, $language, $params, $from, $send);

  watchdog('info', 'Email sent to' . $user['mail']);
}

/**
 * Return all selected users in Workbench Moderation Extras config
 * If none are selected it will return the master user :)
 *
 * @return array
 */
function _workbench_moderation_extras_get_users() {
  $uids = variable_get('workbench_moderation_extras_users');

  // Clean users that lost permissions :)
  if (!empty($uids)) {
    $users = array();
    foreach ($uids as $key => $uid) {
      $user = user_load($uid);
      $users[] = array(
        'name' => $user->name,
        'mail' => $user->mail
      );
    }
  } else {
    $user = user_load(1);
    $users[] = array(
      'name' => $user->name,
      'mail' => $user->email
    );
  }
  return $users;

}

/**
 * Get the list of necessary nodes to change
 * moderation state to Regular Review
 *
 * @return array
 */
function _workbench_moderation_extras_get_published_state_nodes() {
  $node_types = variable_get('workbench_moderation_extras_node_types');
  $nodes = db_select('workbench_moderation_node_history', 'wmnh');
  $nodes->fields('wmnh', array('nid'));
  $nodes->join('node', 'node', '(wmnh.nid=node.nid)');
//  $nodes->condition('wmnh.from_state', 'regular_review', '!=');
  $nodes->condition('wmnh.state', 'published');
  $nodes->condition('wmnh.published', 1);
  $nodes->condition('wmnh.is_current', 1);
  if (is_array($node_types) AND !empty($node_types)) {
    $nodes_or = db_or();
    foreach ($node_types as $type) {
      $nodes_or->condition('node.type', $type);
    }
    $nodes->condition($nodes_or);
  }
  $nodes->condition('wmnh.stamp', time() - variable_get('workbench_moderation_extras_time', 3600 * 24 * 7), '<'); // only if lower then expiration time
  $nodes = $nodes->execute();
  $nids = array();
  foreach ($nodes as $node) {
    $nids[] = $node->nid;
  }
  return $nids;
}

/**
 *
 */
function _workbench_moderation_extras_change_state($nid) {
  $node = node_load($nid);
  $node->revision = 1;
  $node->log = t('This node needs a Regular review');
  workbench_moderation_moderate($node, 'regular_review'); // set current one to regular review
  node_save($node);
  unset($node);
}
