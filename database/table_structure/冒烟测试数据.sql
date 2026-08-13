-- ============================================================================
-- 冒烟测试数据 (Smoke Test Seed Data)
--
-- 用途：为 add-jwt-interceptor change 的冒烟测试提供可重复运行的测试数据
-- 包含：2 个测试用户、3 个家族表、6 个成员、5 条关系、4 条事件
--
-- 测试账号：
--   用户名: testuser   密码: 123456   (id=1000) —— 主测试账号，拥有家族表 1000/1001
--   用户名: testuser2  密码: 123456   (id=1001) —— 越权测试账号，拥有家族表 1002
--
-- 用 testuser2 登录后访问 testuser 的家族表 → 应能拿到数据（本 change 不做 IDOR 防护，
--   属于延后到 add-user-context 的范围）；但不带 token 访问任何受保护端点 → 401
--
-- 安全特性：可重复运行（幂等），每次运行先 DELETE 测试数据再插入，不影响业务数据
-- 数据范围：所有测试数据 id >= 1000，与现有 AUTO_INCREMENT 起始值（3/7/8/1/7）隔离
-- ============================================================================

-- 关闭外键检查，便于按任意顺序清理与插入
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------------------------------------------------------
-- 1. 清理历史测试数据（幂等：可重复运行）
-- ----------------------------------------------------------------------------
DELETE FROM `event`          WHERE id >= 1000 OR member_id >= 1000;
DELETE FROM `relationship`   WHERE member_id1 >= 1000 OR member_id2 >= 1000;
DELETE FROM `member`         WHERE id >= 1000;
DELETE FROM `family_table`   WHERE id >= 1000 OR user_id >= 1000;
DELETE FROM `user`           WHERE id >= 1000 OR username IN ('testuser', 'testuser2');

-- 重置 AUTO_INCREMENT，避免插入显式 id 后计数器不前移导致后续业务插入冲突
ALTER TABLE `user`         AUTO_INCREMENT = 1000;
ALTER TABLE `family_table` AUTO_INCREMENT = 1000;
ALTER TABLE `member`       AUTO_INCREMENT = 1000;
ALTER TABLE `event`        AUTO_INCREMENT = 1000;

-- ----------------------------------------------------------------------------
-- 2. 用户表（2 个测试账号）
-- ----------------------------------------------------------------------------
-- 密码明文存储（与现有 UserController.verifyUser 行为一致，BCrypt 延后到 harden-security）
INSERT INTO `user` (`id`, `username`, `password`) VALUES
  (1000, 'testuser',  '123456'),
  (1001, 'testuser2', '123456');

-- ----------------------------------------------------------------------------
-- 3. 家族表（3 个，分布在不同用户下）
-- ----------------------------------------------------------------------------
-- 1000、1001 属于 testuser；1002 属于 testuser2（用于越权测试）
INSERT INTO `family_table` (`id`, `table_name`, `content`, `establish_time`, `user_id`) VALUES
  (1000, '测试家族-张氏家谱',    '测试用主家族表',           '1990-01-01', 1000),
  (1001, '测试家族-李氏家谱',    'testuser 的第二个家族表',  '2000-05-15', 1000),
  (1002, '测试家族-王氏家谱',    'testuser2 的家族表',       '1985-08-20', 1001);

-- ----------------------------------------------------------------------------
-- 4. 成员表（6 个成员，全部分布在家族表 1000 中，便于测试家谱树）
-- ----------------------------------------------------------------------------
-- 结构：张三(父) + 李四(母) → 张小明、张小红
--       外加：王五（孤立成员，无关系，用于测试空关系场景）
INSERT INTO `member` (`id`, `name`, `gender`, `birthdate`, `deathdate`, `bio`, `family_table_id`) VALUES
  (1000, '张三',     '男', '1960-03-10', NULL,       '测试家族族长',      1000),
  (1001, '李四',     '女', '1962-07-22', NULL,       '张三之妻',          1000),
  (1002, '张小明',   '男', '1985-09-15', NULL,       '张三长子',          1000),
  (1003, '张小红',   '女', '1988-12-05', NULL,       '张三长女',          1000),
  (1004, '王小宝',   '男', '2010-04-18', NULL,       '张小明之子（第三代）', 1000),
  (1005, '王五',     '男', '1955-02-01', '2020-11-30', '孤立测试成员，无关系', 1000);

-- ----------------------------------------------------------------------------
-- 5. 关系表（5 条父子/母子关系）
-- ----------------------------------------------------------------------------
-- 约定：member_id1 = 父/母，member_id2 = 子/女
-- relation 字段取值：父亲 / 母亲 / 儿子 / 女儿（与前端 Familytree.vue 选项一致）
INSERT INTO `relationship` (`member_id1`, `member_id2`, `relation`) VALUES
  (1000, 1002, '父亲'),  -- 张三 -> 张小明
  (1000, 1003, '父亲'),  -- 张三 -> 张小红
  (1001, 1002, '母亲'),  -- 李四 -> 张小明
  (1001, 1003, '母亲'),  -- 李四 -> 张小红
  (1002, 1004, '父亲');  -- 张小明 -> 王小宝

-- ----------------------------------------------------------------------------
-- 6. 事件表（4 条事件，分布在不同成员上）
-- ----------------------------------------------------------------------------
INSERT INTO `event` (`member_id`, `event_date`, `event_type`, `event_description`, `id`) VALUES
  (1000, '1960-03-10', '出生', '张三出生',           1000),
  (1000, '1985-09-20', '结婚', '张三与李四结婚',     1001),
  (1002, '1985-09-15', '出生', '张小明出生',         1002),
  (1002, '2010-04-18', '生子', '张小明之子王小宝出生', 1003);

-- 重新开启外键检查
SET FOREIGN_KEY_CHECKS = 1;

-- ============================================================================
-- 验证查询（可选执行，确认数据已正确插入）
-- ============================================================================
-- SELECT id, username, password FROM `user` WHERE id >= 1000;
-- SELECT id, table_name, user_id FROM `family_table` WHERE id >= 1000;
-- SELECT id, name, gender, family_table_id FROM `member` WHERE id >= 1000;
-- SELECT member_id1, member_id2, relation FROM `relationship` WHERE member_id1 >= 1000;
-- SELECT id, member_id, event_type FROM `event` WHERE id >= 1000;

-- ============================================================================
-- 冒烟测试用 curl 命令速查（后端启动后，在另一终端执行）
-- ============================================================================
-- # 1. 登录获取 token（白名单端点，无需 Authorization）
-- curl -X POST "http://localhost:8080/user/login?username=testuser&password=123456"
--
-- # 2. 不带 token 访问受保护端点 → 期望 401
-- curl -i http://localhost:8080/family-table/user/1000
-- curl -i http://localhost:8080/family-tree/1000
-- curl -i http://localhost:8080/member/findall
-- curl -i http://localhost:8080/relation/findall
-- curl -i http://localhost:8080/event/findall
-- curl -i http://localhost:8080/family-table/findall
--
-- # 3. 带无效 token → 期望 401
-- curl -i -H "Authorization: Bearer garbage" http://localhost:8080/family-tree/1000
-- curl -i -H "Authorization: Basic abc123"   http://localhost:8080/family-tree/1000
--
-- # 4. 带有效 token → 期望 200（TOKEN 替换为步骤 1 返回的 data.token）
-- curl -i -H "Authorization: Bearer TOKEN" http://localhost:8080/family-table/user/1000
-- curl -i -H "Authorization: Bearer TOKEN" http://localhost:8080/family-tree/1000
-- curl -i -H "Authorization: Bearer TOKEN" http://localhost:8080/member/findall
