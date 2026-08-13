-- ============================================================================
-- 密码迁移 SQL —— harden-security change
-- ============================================================================
-- 用途：把 user.password 列从明文迁移到 BCrypt 哈希
-- 关联变更：openspec/changes/harden-security/
-- 关联代码：common/util/PasswordUtil.java（BCryptPasswordEncoder, strength=10）
-- ============================================================================
--
-- 执行顺序：
--   1. ALTER TABLE 扩展 password 列长度（varchar(20) → varchar(100)）
--   2. UPDATE 测试账号（id=1000, 1001）的 password 为 BCrypt 哈希
--   3. 业务账号（id < 1000）由用户根据真实密码另行 UPDATE
--
-- 测试账号明文：123456
-- 测试账号哈希（BCrypt strength=10）：
--   $2a$10$2Mom1xn09HW.qFzSl5C3cuOE60MYF.D99wlJaF05/AHdtKLdHL.9q
--
-- 哈希生成方式（可在 Java 中复现）：
--   new BCryptPasswordEncoder(10).encode("123456")
-- 注意：BCrypt 每次生成的 salt 不同，但 matches() 均能验证通过
-- ============================================================================

-- 1. 扩展 password 列长度（BCrypt 哈希固定 60 字符，留余量到 100）
ALTER TABLE `user` MODIFY COLUMN `password` varchar(100) DEFAULT NULL;

-- 2. 测试账号迁移（id=1000, 1001，明文均为 123456）
UPDATE `user`
SET `password` = '$2a$10$2Mom1xn09HW.qFzSl5C3cuOE60MYF.D99wlJaF05/AHdtKLdHL.9q'
WHERE `id` IN (1000, 1001);

-- 3. 业务账号迁移（id < 1000）—— 需用户根据真实明文密码生成 BCrypt 哈希后填入
-- 示例（替换 <hash> 为 new BCryptPasswordEncoder(10).encode("真实密码")）：
-- UPDATE `user` SET `password` = '<hash>' WHERE `id` = 1;
-- UPDATE `user` SET `password` = '<hash>' WHERE `id` = 2;

-- ============================================================================
-- 验证查询（执行后确认 password 列已更新为 $2a$10$ 开头的哈希字符串）
-- ============================================================================
-- SELECT id, username, password FROM `user` WHERE id IN (1000, 1001);
-- 期望结果：
--   1000 | testuser  | $2a$10$2Mom1xn09HW.qFzSl5C3cuOE60MYF.D99wlJaF05/AHdtKLdHL.9q
--   1001 | testuser2 | $2a$10$2Mom1xn09HW.qFzSl5C3cuOE60MYF.D99wlJaF05/AHdtKLdHL.9q
