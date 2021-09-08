   const addon = require('./build/Release/addon')
   const express = require('express')
   const path = require('path')
   const app = express()
   const PORT = process.env.PORT ?? 3000

   app.use(express.urlencoded({extended: true}))
   app.post('/create', (req,res)=>{

      const user = req.body.title
      const isUserPresent = addon.getWindowsUser(user)
      if (isUserPresent === 1){
         res.sendFile(path.resolve(__dirname, 'static', 'indexGotUser.html'))
      } else {
         res.sendFile(path.resolve(__dirname, 'static', 'indexNoUser.html'))
      }
   })
   app.get('/back',(req,res)=>{
      res.sendFile(path.resolve(__dirname, 'static', 'index.html'))
   })
   app.use(express.static(path.resolve(__dirname, 'static')))

   app.listen(PORT, () => {
      console.log(`Server has been started on ${PORT}...`)
   })