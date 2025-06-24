<template>
  <div>
    <div class="member-history">
    <h1>个人信息</h1>
    <el-card>
      <label for="name">姓名:</label>
      <input type="name" v-if="readonly===false" id="name" v-model="member.name" :disabled="readonly" required/>
      <el-text v-else> {{ member.name }}</el-text>
      <label for="dob">出生日期:</label>
      <input type="date" v-if="readonly===false" id="dob" v-model="member.dob" :disabled="readonly" required/>
      <el-text v-else> {{ member.dob }}</el-text>
      <label for="marrigedate">性别:</label>
      <select v-if="readonly===false" v-model="member.gender" :disabled="readonly" required>
        <option value="男">男</option>
        <option value="女">女</option>
      </select>
      <el-text v-else> {{ member.gender }}</el-text>
      <label for="deathdate">死亡日期:</label>
      <input type="date" v-if="readonly===false" id="deathdate" v-model="member.deathDate" :disabled="readonly" required/>
      <el-text v-else> {{ member.deathDate }}</el-text>
      <label for="bio">生平简介:</label>
      <input type="bio" v-if="readonly===false" id="bio" v-model="member.bio" :disabled="readonly" required/>
      <el-text v-else> {{ member.bio }}</el-text>
    </el-card>
    <button v-if="readonly==true" @click="edit">编辑履历</button>
    <button v-else @click="submit">提交履历</button>
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
        dob: '无',
        gender: '男',
        deathDate: '无',
        bio: '',
      },
      readonly:true,
    };
  },
  methods: {
    saveUserInfo:function() {
      // Save user info in cookies
      this.$cookies.set('name', this.name, 60*2);
      this.$cookies.set('dob', this.dob, 60*2);
      this.$cookies.set('gender', this.gender, 60*2);
      this.$cookies.set('deathDate', this.deathDate, 60*2 );
      this.$cookies.set('bio', this.bio, 60*2 );
      this.loadUserInfo();
    },
    loadUserInfo:function() {
      this.name = this.$cookies.get('name');
      this.dob = this.$cookies.get('dob');
      this.gender = this.$cookies.get('gender');
      this.deathDate = this.$cookies.get('deathDate');
      this.bio = this.$cookies.get('bio');
    },
    edit:function() {
      ElMessageBox.confirm('您确定进行编辑吗？是否继续', '警告',{
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
        }).then(() => {
        ElMessage({
        type: 'success',
        message: '已确认'
        });
        this.readonly = !this.readonly;
        }).catch((err) => {
        ElMessage({
        type: 'info',
        message: '取消操作' + err,
        });
        this.readonly = this.readonly;
        });
    },
    submit:function(){
      ElMessageBox.confirm('您确定进行提交吗？是否继续', '警告',{
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
        }).then(() => {
        ElMessage({
        type: 'success',
        message: '已提交'
        });
        this.saveUserInfo();
        this.readonly = !this.readonly;
        }).catch((err) => {
        ElMessage({
        type: 'info',
        message: '取消操作' + err,
        });
        this.readonly = this.readonly;
        });
    }
  },
  mounted() {
    // 访问组件的 DOM 元素
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
.el-card{
  margin: 8px;
  padding: 8px;
  text-align: left;
}
input, select{
  width: 400px;
  padding: 8px;
  margin: 8px 0;
}
button {
  width: 60%;
  padding: 10px;
  background-color: #4CAF50;
  color: white;
  border: none;
  margin-top: 20px;
  
  cursor: pointer;
}
</style>
