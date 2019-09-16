-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: classmysql.engr.oregonstate.edu:3306
-- Generation Time: May 30, 2019 at 07:40 AM
-- Server version: 10.3.13-MariaDB-log
-- PHP Version: 7.0.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cs340_weinertn`
--

-- --------------------------------------------------------

--
-- Table structure for table `state`
--

CREATE TABLE `state` (
  `stateId` int(11) NOT NULL,
  `stateCode` varchar(2) NOT NULL,
  `stateName` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `state`
--

INSERT INTO `state` (`stateId`, `stateCode`, `stateName`) VALUES
(1, 'AL', 'Alabama'),
(2, 'AK', 'Alaska'),
(3, 'AZ', 'Arizona'),
(4, 'AR', 'Arkansas'),
(5, 'CA', 'California'),
(6, 'CO', 'Colorado'),
(7, 'CT', 'Connecticut'),
(8, 'DE', 'Delaware'),
(9, 'DC', 'District of Columbia'),
(10, 'FL', 'Florida'),
(11, 'GA', 'Georgia'),
(12, 'HI', 'Hawaii'),
(13, 'ID', 'Idaho'),
(14, 'IL', 'Illinois'),
(15, 'IN', 'Indiana'),
(16, 'IA', 'Iowa'),
(17, 'KS', 'Kansas'),
(18, 'KY', 'Kentucky'),
(19, 'LA', 'Louisiana'),
(20, 'ME', 'Maine'),
(21, 'MD', 'Maryland'),
(22, 'MA', 'Massachusetts'),
(23, 'MI', 'Michigan'),
(24, 'MN', 'Minnesota'),
(25, 'MS', 'Mississippi'),
(26, 'MO', 'Missouri'),
(27, 'MT', 'Montana'),
(28, 'NE', 'Nebraska'),
(29, 'NV', 'Nevada'),
(30, 'NH', 'New Hampshire'),
(31, 'NJ', 'New Jersey'),
(32, 'NM', 'New Mexico'),
(33, 'NY', 'New York'),
(34, 'NC', 'North Carolina'),
(35, 'ND', 'North Dakota'),
(36, 'OH', 'Ohio'),
(37, 'OK', 'Oklahoma'),
(38, 'OR', 'Oregon'),
(39, 'PA', 'Pennsylvania'),
(40, 'PR', 'Puerto Rico'),
(41, 'RI', 'Rhode Island'),
(42, 'SC', 'South Carolina'),
(43, 'SD', 'South Dakota'),
(44, 'TN', 'Tennessee'),
(45, 'TX', 'Texas'),
(46, 'UT', 'Utah'),
(47, 'VT', 'Vermont'),
(48, 'VA', 'Virginia'),
(49, 'WA', 'Washington'),
(50, 'WV', 'West Virginia'),
(51, 'WI', 'Wisconsin'),
(52, 'WY', 'Wyoming'),
(53, 'NA', 'No State');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `state`
--
ALTER TABLE `state`
  ADD PRIMARY KEY (`stateId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `state`
--
ALTER TABLE `state`
  MODIFY `stateId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=54;
COMMIT;



--
-- Table structure for table `Record_Label`
--

CREATE TABLE `Record_Label` (
  `labelId` int(11) NOT NULL,
  `labelName` varchar(50) DEFAULT NULL,
  `labelCity` varchar(50) DEFAULT NULL,
  `labelState` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `Record_Label`
--

INSERT INTO `Record_Label` (`labelId`, `labelName`, `labelCity`, `labelState`) VALUES
(12, 'Capitol Records Nashville', 'Nashville', 44),
(13, 'Mercury Records', 'Chicago', 14),
(14, 'No Record Label', '', 53);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Record_Label`
--
ALTER TABLE `Record_Label`
  ADD PRIMARY KEY (`labelId`),
  ADD KEY `stateCode` (`labelState`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Record_Label`
--
ALTER TABLE `Record_Label`
  MODIFY `labelId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
COMMIT;



--
-- Table structure for table `Genre`
--

CREATE TABLE `Genre` (
  `genreID` int(11) NOT NULL,
  `genreName` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `Genre`
--

INSERT INTO `Genre` (`genreID`, `genreName`) VALUES
(10, 'Country'),
(11, 'Rock'),
(12, 'Classic Rock');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Genre`
--
ALTER TABLE `Genre`
  ADD PRIMARY KEY (`genreID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Genre`
--
ALTER TABLE `Genre`
  MODIFY `genreID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;
COMMIT;



--
-- Table structure for table `Artist`
--

CREATE TABLE `Artist` (
  `artistId` int(11) NOT NULL,
  `labelId` int(11) DEFAULT NULL,
  `artistFirstName` varchar(50) NOT NULL,
  `artistLastName` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `Artist`
--

INSERT INTO `Artist` (`artistId`, `labelId`, `artistFirstName`, `artistLastName`) VALUES
(12, 12, 'Carrie', 'Underwood'),
(13, 13, 'Jon', 'Bon Jovi'),
(14, 14, 'Paul', 'McCartney'),
(15, 14, 'Michael', 'Jackson');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Artist`
--
ALTER TABLE `Artist`
  ADD PRIMARY KEY (`artistId`),
  ADD KEY `labelId` (`labelId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Artist`
--
ALTER TABLE `Artist`
  MODIFY `artistId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `Artist`
--
ALTER TABLE `Artist`
  ADD CONSTRAINT `Artist_ibfk_1` FOREIGN KEY (`labelId`) REFERENCES `Record_Label` (`labelId`) ON DELETE SET NULL ON UPDATE SET NULL;
COMMIT;



--
-- Table structure for table `Song`
--

CREATE TABLE `Song` (
  `id` int(11) NOT NULL,
  `labelId` int(11) DEFAULT NULL,
  `name` varchar(50) NOT NULL,
  `length` time NOT NULL,
  `releaseYear` int(9) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `Song`
--

INSERT INTO `Song` (`id`, `labelId`, `name`, `length`, `releaseYear`) VALUES
(70, NULL, 'Say Say Say', '00:03:55', 1983),
(71, 12, 'Before He Cheats', '00:03:19', 2005),
(72, 13, 'Livin\' on a Prayer', '00:04:11', 1986);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Song`
--
ALTER TABLE `Song`
  ADD PRIMARY KEY (`id`),
  ADD KEY `labelId` (`labelId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Song`
--
ALTER TABLE `Song`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=73;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `Song`
--
ALTER TABLE `Song`
  ADD CONSTRAINT `Song_ibfk_1` FOREIGN KEY (`labelId`) REFERENCES `Record_Label` (`labelId`) ON DELETE SET NULL ON UPDATE SET NULL;
COMMIT;



--
-- Table structure for table `songsToArtist`
--

CREATE TABLE `songsToArtist` (
  `songId` int(11) NOT NULL,
  `artistId` int(11) NOT NULL,
  `primaryOrFeatured` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `songsToArtist`
--

INSERT INTO `songsToArtist` (`songId`, `artistId`, `primaryOrFeatured`) VALUES
(70, 14, NULL),
(70, 15, NULL),
(71, 12, NULL),
(72, 13, NULL);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `songsToArtist`
--
ALTER TABLE `songsToArtist`
  ADD PRIMARY KEY (`songId`,`artistId`),
  ADD KEY `songId` (`songId`),
  ADD KEY `artistId` (`artistId`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `songsToArtist`
--
ALTER TABLE `songsToArtist`
  ADD CONSTRAINT `songsToArtist_ibfk_1` FOREIGN KEY (`songId`) REFERENCES `Song` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `songsToArtist_ibfk_2` FOREIGN KEY (`artistId`) REFERENCES `Artist` (`artistId`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;



--
-- Table structure for table `songsToGenres`
--

CREATE TABLE `songsToGenres` (
  `songId` int(11) NOT NULL,
  `genreId` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `songsToGenres`
--

INSERT INTO `songsToGenres` (`songId`, `genreId`) VALUES
(70, 11),
(71, 10),
(72, 11),
(72, 12);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `songsToGenres`
--
ALTER TABLE `songsToGenres`
  ADD PRIMARY KEY (`songId`,`genreId`),
  ADD KEY `songId` (`songId`),
  ADD KEY `genreId` (`genreId`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `songsToGenres`
--
ALTER TABLE `songsToGenres`
  ADD CONSTRAINT `songsToGenres_ibfk_1` FOREIGN KEY (`genreId`) REFERENCES `Genre` (`genreID`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `songsToGenres_ibfk_2` FOREIGN KEY (`songId`) REFERENCES `Song` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
