<?php
/**
 * @file
 */

/**
 * class
   $UserQuery = new UserQuery();
   $UserQuery->allUserUid();
 *
 */
class UserQuery {
  /**
   * @parameter ,
   *
   * @return array,
   * all Meeting NID
   */
  public function allUserUid() {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'user')
      ->propertyCondition('status', 1);

    $result = $query->execute();

    $uid_array = NULL;
    if (isset($result['user'])) {
      if (count($result['user']) > 0 ) {
        $uid_array = array_keys($result['user']);
      }
    }

    return $uid_array;
  }

  /**
   * @param array, Specify Role RID
   * authenticated User 2
   * administrator 3
   *
   * @return array
   *  user Uid list
   */
  public function allUserUidByRole($role_id_array = NULL, $active_user = TRUE) {
    $user_uid_array = array();

    if (!$role_id_array) {
      return $user_uid_array;
    }
    if (!(count($this->allUserUid()) > 0)) {
      return $user_uid_array;
    }

    // load all user, check if user role is match, if it is true, push to array
    $users = user_load_multiple($this->allUserUid());
    foreach($users as $user) {
      if (array_intersect($role_id_array, array_keys($user->roles))) {
        $user_uid_array[] = $user->uid;
      }
    }

    return $user_uid_array;
  }

}
