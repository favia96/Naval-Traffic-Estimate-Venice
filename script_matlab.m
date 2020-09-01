%% traffico navale
% Progetto ETI: Federico Favia e Martin De Pellegrini
clear all
close all
clc

%% lettura file txt col numero di blob contati in ogni frame
filename = '<filename.txt>'; 
delimiterIn = ' ';
blob_1 = importdata(filename,delimiterIn); %perde un tot di frame iniziali dovuti all'adaptive bg sub

%% inizializzazione variabili
fps = 30; % frame per secondo video
T = 299; %[s] tempo totale, per video da 5 min
%T = 148; %[s] tempo totale, per video da 2.5 min
%T = 100; %[s] tempo totale, per video da 1.7 min
%T = 75; %[s] tempo totale, per video da 1.25 min
%T = 1328; % [s] tempo totale, per video da 22 min 28 sec

frame = (1:fps*T)'; %apice=trasposto --> vettore riga trasf a colonna

L = length(frame)-length(blob_1);
blob = zeros(fps*T,1);
for i = 1:length(blob_1);
    blob(L+i,:)=blob_1(i,:);
end

subframe = (1:fps:fps*T)';

time  = (0:1/fps:T-1/fps)'; %step 1/fps [s]

subtime = (0:T-1)';

video = [frame,blob]; %matrice video composta da 1^col frame e 2^col #blob, non usata

%% MEDIA INTEGRALE
k = 1;
for i = 1:length(blob);
    media_barche(i,:) = mean(blob(1:i)); %media barche al passare di ogni frame
    if i == k*fps
        media_barche_salvate(k,:) = media_barche(i,:); %media ogni fps frame
        k = k+1;
    end    
end

%% MEDIANA
h = 1;
for i= 1:length(blob);
    mediana_barche(i,:)= median(blob(1:i)); %mediana barche al passare di ogni frame
    if i == h*fps
        mediana_barche_salvate(h,:) = mediana_barche(i,:); %mediana ogni fps frame
        h = h+1;
    end   
end

%% FLUSSO O BARCHE/S
for i = 1:length(media_barche)-1
    flusso(i,:) = (media_barche(i+1)-media_barche(i))/(1/fps); % diviso l'intervallo di tempo che è (1/fps) in secondi
end
flusso_medio = mean(flusso); %flusso medio

%% PLOT 1 (frame) - 2 subplots
%figure()
figure('units','normalized','outerposition',[0 0 1 1])
subplot(1,2,1),hold on, grid on
plot(frame,blob);
title('#barche over frames')
xlabel('frame')
ylabel('#barche')
subplot(1,2,2),hold on, grid on %1 riga 2 colonne per mettere grafici, terzo numero dove posiziono il grafico
plot(subframe,media_barche_salvate,'-k','LineWidth',1) %black 
plot(subframe,mediana_barche_salvate,'-r','LineWidth',1) %red
xlabel('frame')
ylabel('#barche')
title ('Media #barche over frames')
legend('Media','Mediana','location','southeast')
saveas(gcf,'MM_DD_hh.mm_DAY_frame_plots.png')

%% PLOT 2 (time) - 3 subplots
%figure()
figure('units','normalized','outerposition',[0 0 1 1])
subplot(1,3,1), hold on, grid on
plot(subtime,media_barche_salvate,'-k','LineWidth',1)
plot(subtime,mediana_barche_salvate,'-r','LineWidth',1)
xlabel('t [s]')
ylabel('#barche')
title ('#barche over time')
legend('Media','Mediana','location','southeast')

subplot(1,3,2), hold on, grid on
plot(time(2:end),flusso,'-k','LineWidth',1)
ylabel('#barche/s')
xlabel('t[s]')
title('Flusso di barche over time')

p=polyfit(time(2:end),flusso,3) %polinomio che fitta di ordine 3
y1=polyval(p,time(2:end));
subplot(1,3,3), hold on, grid on
plot(time(2:end),flusso,'o')
plot(time(2:end),y1,'LineWidth',2)
ylabel('flusso');
xlabel('t[s]')
title('Andamento del flusso')
saveas(gcf,'MM_DD_hh.mm_DAY_time_plots.png')

