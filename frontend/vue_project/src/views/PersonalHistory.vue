<template>
  <div>
    <div class="member-history">
      <h1>个人信息</h1>
        <el-form :model="member" label-width="80px">
          <el-form-item label="姓名">
            <el-input v-model="member.name" :disabled="readonly" placeholder="请输入姓名" />
          </el-form-item>
          <el-form-item label="出生日期" prop="dob">
            <el-date-picker 
              v-model="member.dob" 
              type="date" 
              :disabled="readonly" 
              placeholder="选择出生日期" 
              format="YYYY-MM-DD"
              value-format="YYYY-MM-DD"
              style="width: 100%;" 
            />
          </el-form-item>
          <el-form-item label="性别">
            <el-select v-model="member.gender" :disabled="readonly" placeholder="请选择性别" style="width: 100%;">
              <el-option label="男" value="男" />
              <el-option label="女" value="女" />
            </el-select>
          </el-form-item>
          <el-form-item label="死亡日期">
            <el-date-picker v-model="member.deathDate" type="date" :disabled="readonly" placeholder="选择死亡日期" style="width: 100%;" />
          </el-form-item>
          <el-form-item label="生平简介">
            <el-input v-model="member.bio" :disabled="readonly" placeholder="请输入生平简介" />
          </el-form-item>
          <el-form-item>
            <el-button v-if="readonly" type="primary" @click="edit">编辑履历</el-button>
            <el-button v-else type="success" @click="submit">提交履历</el-button>
          </el-form-item>
        </el-form>
    </div>
  </div>
</template>

<script>
import { ElMessageBox, ElMessage } from 'element-plus';
export default {
  data() {
    return {
      member: {
        name: '',
        dob: '',
        gender: '男',
        deathDate: '',
        bio: '',
      },
      readonly: true,
    };
  },
  methods: {
    saveUserInfo() {
      // 使用 store 保存个人信息
      this.$store.commit('SET_MEMBERS', [this.member]);
      // 同时保存到 localStorage 作为备份
      localStorage.setItem('member', JSON.stringify(this.member));
    },
    loadUserInfo() {
      // 优先从 store 读取，如果没有则从 localStorage 读取
      const storeMembers = this.$store.getters.members;
      if (storeMembers.length > 0) {
        this.member = storeMembers[0];
      } else {
        const saved = localStorage.getItem('member');
        if (saved) {
          this.member = JSON.parse(saved);
        }
      }
    },
    edit() {
      ElMessageBox.confirm('您确定进行编辑吗？是否继续', '警告', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        ElMessage({
          type: 'success',
          message: '已确认'
        });
        this.readonly = false;
      }).catch((err) => {
        ElMessage({
          type: 'info',
          message: '取消操作' + err,
        });
      });
    },
    submit() {
      ElMessageBox.confirm('您确定进行提交吗？是否继续', '警告', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        ElMessage({
          type: 'success',
          message: '已提交'
        });
        this.saveUserInfo();
        this.readonly = true;
      }).catch((err) => {
        ElMessage({
          type: 'info',
          message: '取消操作' + err,
        });
      });
    }
  },
  mounted() {
    this.loadUserInfo();
  }
};
</script>

<style scoped>
.member-history {
  max-width: 500px;
  margin-left: 30%;
  text-align: center;
}
label {
  display: block;
  margin-top: 10px;
}
.el-card {
  margin: 8px;
  padding: 8px;
  text-align: left;
}
input, select {
  width: 400px;
  padding: 8px;
  margin: 8px 0;
}
button, .el-button {
  width: 60%;
  padding: 10px;
  background-color: #4CAF50;
  color: white;
  border: none;
  margin-top: 20px;
  cursor: pointer;
}
.main-bg {
  background: #fff;
  border-radius: 12px;
  box-shadow: 0 2px 12px rgba(0,0,0,0.08);
  padding: 32px 24px;
  min-height: 400px; /* 可根据需要调整 */
  margin: 32px auto;
  max-width: 900px;  /* 可根据需要调整 */
}
</style> 