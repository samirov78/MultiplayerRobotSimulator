var express = require('express');
var router = express.Router();
var fs   = require('fs');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index');
});

router.get('/index', function(req, res, next) {
  res.render('index');
});

router.get('/profiles', function (req, res) {
  res.set('Content-Type', 'text/xml');
  res.send(fs.readFileSync('../Serveur/Exe/DB/Profiles/profiles.xml', {encoding: 'utf-8'}))
// res.send(fs.readFileSync('../../Exe/DB/Profiles/cards.xml', {encoding: 'utf-8'}))
  });
router.get('/cards', function (req, res) {
  res.set('Content-Type', 'text/xml');
  //res.send(fs.readFileSync('../../Exe/DB/Profiles/profiles.xml', {encoding: 'utf-8'}))
 res.send(fs.readFileSync('../Serveur/Exe/DB/Profiles/cards.xml', {encoding: 'utf-8'}))
  });
router.get('/image', function (req, res) {
  req.param(image);
  res.set('Content-Type', 'image/png');
  //res.send(fs.readFileSync('../../Exe/DB/Profiles/profiles.xml', {encoding: 'utf-8'}))
 res.send(fs.readFileSync('', {encoding: 'utf-8'}))
  });

module.exports = router;
